#include <dlfcn.h>
#include <iostream>
#include <map>
#include <optional>

#include "ai.hh"
#include "listener_manager.hh"
#include "logger.hh"
#include "uci.hh"
#include "utils.hh"

namespace listener
{

    ListenerManager::ListenerManager(std::vector<std::string> filenames,
                                     board::Chessboard& board)
        : board_(board)
    {
        for (auto filename : filenames)
        {
            void* handle = dlopen(filename.c_str(), RTLD_LAZY);
            if (!handle)
            {
                std::cerr << "Cannot handle listener: " << dlerror() << "\n";
                throw std::runtime_error("listener_not_loaded");
            }

            dlerror();

            Listener *listener = reinterpret_cast<Listener*(*)()>
                                    (dlsym(handle, "listener_create"))();
            const char* dlsym_error = dlerror();
            if (dlsym_error)
            {
                std::cerr << "Cannot load symbol create: "
                          << dlsym_error << '\n';
                throw std::runtime_error("create_not_found");
            }

            listeners_.push_back(listener);
            handles_.push_back(handle);
        }
    }

    /*static board::Position ask_for_pos(std::string pos)
    {
        auto tmp = std::string();
        std::cerr << "Enter " << pos << " position: ";
        std::cin >> tmp;
        return board::Position(static_cast<board::File>(tmp.at(0) - 'A'),
                               static_cast<board::Rank>(tmp.at(1) - '1'));
    }*/

    board::Move
    ListenerManager::get_move(const std::optional<board::PgnMove>& pgn_opt)
    {
        // Human Player
        board::Move move;
        /*if (mode == 0)
        {
            bool valid = false;
            while (!valid)
            {
                auto src_pos = ask_for_pos("src");
                auto dst_pos = ask_for_pos("dst");
                move = board_.create_move(src_pos, dst_pos, std::nullopt);
                if (move.src_state_get() != 0)
                    valid = true;
                else
                    std::cerr << "\nThis move is not a valid move,"
                              << " please enter another move:\n\n";
            }

            return move;
            }*/

        if (!pgn_opt)
        {
            std::vector<board::Move> legal_moves =
                board_.generate_legal_moves();
            return ai::AI::search(board_);
        }
        auto pgn_move = pgn_opt.value();

        move = board_.create_move(pgn_move.start_get(), pgn_move.end_get(),
                                  pgn_move.promotion_get());

        // Return move if move is legal otherwise disqualify.
        if (move.src_state_get() != 0
            && move.piece_get() == pgn_move.piece_get()
            && static_cast<bool>(move.capture_get()) == pgn_move.capture_get())
            return move;

        signal_move(move,true);
        on_player_disqualified(static_cast<board::Color>
                               (!board_.white_turn_get()));
        on_game_finished();
        exit(0);
    }

    static const std::map<board::PieceType, std::string> promotion_uci =
    {
        {board::PieceType::QUEEN, "q"},
        {board::PieceType::ROOK, "r"},
        {board::PieceType::BISHOP, "b"},
        {board::PieceType::KNIGHT, "n"}
    };

    void ListenerManager::signal_move(const board::Move& move, bool is_pgn)
    {
        auto src_pos = move.src_position_get();
        auto dst_pos = move.dst_position_get();
        auto pro = move.promotion_get();
        on_piece_moved(move.piece_get(), src_pos, dst_pos);

        if (move.king_castling_get())
            on_kingside_castling(static_cast<board::Color>
                                 (board_.white_turn_get()));
        else if (move.queen_castling_get())
            on_queenside_castling(static_cast<board::Color>
                                  (board_.white_turn_get()));
        else
        {
            auto cap = move.capture_get();
            if (cap.has_value())
                on_piece_taken(cap.value(), move.dst_position_get());
            if (pro.has_value())
                on_piece_promoted(pro.value(), move.dst_position_get());
        }

        if (!is_pgn)
            ai::play_move(pos_to_str(false, src_pos)
                          + pos_to_str(false, dst_pos)
                          + (pro.has_value() ? promotion_uci.at(pro.value())
                                            : ""));

        utils::Logger::chessboard(board_.rep_get().generate_ascii_board(12));
    }

    bool ListenerManager::signal_board_state()
    {
        if (board_.is_checkmate())
        {
            on_player_mat(static_cast<board::Color>(!board_.white_turn_get()));
            return true;
        }

        if (board_.is_check())
            on_player_check(static_cast<board::Color>
                            (!board_.white_turn_get()));

        bool stalemate = false;
        if (board_.is_stalemate())
        {
            on_player_pat(static_cast<board::Color>(!board_.white_turn_get()));
            stalemate = true;
        }

        if (stalemate || board_.is_draw())
        {
            on_draw();
            return true;
        }
        return false;
    }

    void ListenerManager::play(const std::vector<board::PgnMove>& pgn_moves,
                               bool is_pgn)
    {
        size_t pgn_idx = 0;
        if (!is_pgn)
            ai::init("R. Giskard Reventlov");

        board::Move move;
        while (true)
        {
            if (is_pgn)
            {
                if (pgn_idx == pgn_moves.size())
                    return;
                move = get_move(std::optional<board::PgnMove>(
                                pgn_moves[pgn_idx++]));
            }
            else
            {
                ai::setup(board_);
                if (signal_board_state()) // check if game is done
                    break;
                move = get_move(std::nullopt);
            }
            if (move.src_state_get() != 0)
                board_.do_move(move, true);
            signal_move(move, is_pgn);

            if (signal_board_state()) // check if game is done
                break;
        }
        on_game_finished();
    }

    void ListenerManager::close_listeners()
    {
        for (size_t i = 0; i < listeners_.size(); ++i)
        {
            delete listeners_[i];
            dlclose(handles_[i]);
        }
        listeners_.clear();
        handles_.clear();
    }


    void ListenerManager::register_board
        (const board::ChessboardInterface& board_interface)
    {
        for (auto listener : this->listeners_)
            listener->register_board(board_interface);

        utils::Logger::chessboard(board_.rep_get().generate_ascii_board(12));
    }

    void ListenerManager::on_game_finished()
    {
        for (auto& listener : this->listeners_)
            listener->on_game_finished();
    }

    void ListenerManager::on_piece_moved(const board::PieceType piece,
                                         const board::Position& from,
                                         const board::Position& to)
    {
        for (auto& listener : this->listeners_)
            listener->on_piece_moved(piece, from, to);
    }

    void ListenerManager::on_piece_taken(const board::PieceType piece,
                                         const board::Position& at)
    {
        for (auto& listener : this->listeners_)
            listener->on_piece_taken(piece, at);
    }

    void ListenerManager::on_piece_promoted(const board::PieceType piece,
                                            const board::Position& at)
    {
        for (auto& listener : this->listeners_)
            listener->on_piece_promoted(piece, at);
    }

    void ListenerManager::on_kingside_castling(const board::Color color)
    {
        for (auto& listener : this->listeners_)
            listener->on_kingside_castling(color);
    }

    void ListenerManager::on_queenside_castling(const board::Color color)
    {
        for (auto& listener : this->listeners_)
            listener->on_queenside_castling(color);
    }

    void ListenerManager::on_player_check(const board::Color color)
    {
        for (auto& listener : this->listeners_)
            listener->on_player_check(color);
    }

    void ListenerManager::on_player_mat(const board::Color color)
    {
        for (auto& listener : this->listeners_)
            listener->on_player_mat(color);
    }

    void ListenerManager::on_player_pat(const board::Color color)
    {
        for (auto& listener : this->listeners_)
            listener->on_player_pat(color);
    }

    void ListenerManager::on_player_disqualified(const board::Color color)
    {
        for (auto& listener : this->listeners_)
            listener->on_player_disqualified(color);
    }

    void ListenerManager::on_draw()
    {
        for (auto& listener : this->listeners_)
            listener->on_draw();
    }
}
