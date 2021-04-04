#include <iostream>
#include <map>
#include <sstream>

#include "cli-listener.hh"
#include "position.hh"
#include "piece-type.hh"
#include "color.hh"
#include "utils.hh"
#include "logger.hh"

namespace listener {
    LISTENER_EXPORT(CLIListener)

    /*
    static char opt_to_char(const CLIListener::opt_piece_t& piece)
    {
        if (!piece)
            return '.';

        const std::map<size_t, char> bit_idx_to_char =
            {
                {0, 'Q'}, {1, 'R'}, {2, 'B'}, {3, 'N'}, {4, 'P'}, {5, 'K'},
                {6, 'q'}, {7, 'r'}, {8, 'b'}, {9, 'n'}, {10, 'p'}, {11, 'k'}
            };

        return bit_idx_to_char.at(side_piece_to_bit_idx(piece.value()));
    }

    static void print_board(const board::ChessboardInterface& board)
    {
        for (int i = 7; i >= 0; --i)
        {
            std::cerr << static_cast<char>('1' + i);
            std::cerr << ' ';
            for (size_t j = 0; j < 8; ++j)
            {
                auto pos = board::Position(static_cast<board::File>(j),
                                           static_cast<board::Rank>(i));
                auto piece = board[pos];
                std::cerr << opt_to_char(piece);
                std::cerr << ' ';
            }
            std::cerr << '\n';
        }
        std::cerr << "  A B C D E F G H \n\n";
    }
    */

    void CLIListener::register_board
    (const board::ChessboardInterface& board_interface)
    {
        board_ = &board_interface;
        utils::Logger::listener("Board Registered Successfully.\n");
    }

    void CLIListener::on_game_finished()
    {
        utils::Logger::listener("THE GAME IS DONE !!\n\n");
    }

    void CLIListener::on_piece_moved(const board::PieceType piece,
                                     const board::Position& from,
                                     const board::Position& to)
    {
        const std::map<size_t, char> piece_to_char =
            {{0, 'Q'}, {1, 'R'}, {2, 'B'}, {3, 'N'}, {4, 'P'}, {5, 'K'}};

        std::stringstream str;
        str << "\nTurn " << turn_++ << "\n\n"
                  << piece_to_char.at(static_cast<size_t>(piece)) << ": "
                  << pos_to_str(true, from) << " -> " << pos_to_str(true, to)
                  << "\n\n";

        utils::Logger::listener(str.str());
        // print_board(*board_);
    }

    void CLIListener::on_piece_taken(const board::PieceType piece,
                                     const board::Position& at)
    {
        const std::map<size_t, char> piece_to_char =
            {{0, 'Q'}, {1, 'R'}, {2, 'B'}, {3, 'N'}, {4, 'P'}, {5, 'K'}};

        std::stringstream str;
        str << piece_to_char.at(static_cast<size_t>(piece)) << " at "
                  << pos_to_str(true, at) << " taken.\n";
        utils::Logger::listener(str.str());
    }

    void CLIListener::on_piece_promoted(const board::PieceType piece,
                                        const board::Position& at)
    {
        const std::map<size_t, char> piece_to_char =
            {{0, 'Q'}, {1, 'R'}, {2, 'B'}, {3, 'N'}, {4, 'P'}, {5, 'K'}};

        std::stringstream str;
        str << "pawn promoted to "
                  << piece_to_char.at(static_cast<size_t>(piece)) << " at "
                  << pos_to_str(true, at) << '\n';

        utils::Logger::listener(str.str());
    }

    void CLIListener::on_kingside_castling(const board::Color color)
    {
        std::stringstream str;
        str << "The " << (static_cast<bool>(color) ? "white" : "black")
                  << " player just did a kingside castling.\n";
        utils::Logger::listener(str.str());
    }

    void CLIListener::on_queenside_castling(const board::Color color)
    {
        std::stringstream str;
        str << "The " << (static_cast<bool>(color) ? "white" : "black")
                  << " player just did a queenside castling.\n";
        utils::Logger::listener(str.str());
    }

    void CLIListener::on_player_check(const board::Color color)
    {
        std::stringstream str;
        str << "THE " << (static_cast<bool>(color) ? "WHITE" : "BLACK")
                  << " PLAYER IS IN CHECK.\n";
        utils::Logger::listener(str.str());
    }

    void CLIListener::on_player_mat(const board::Color color)
    {
        std::stringstream str;
        str << "THE " << (static_cast<bool>(color) ? "WHITE" : "BLACK")
                  << " PLAYER IS CHECKMATE.\n";
        utils::Logger::listener(str.str());
    }

    void CLIListener::on_player_pat(const board::Color color)
    {
        std::stringstream str;
        str << "THE " << (static_cast<bool>(color) ? "WHITE" : "BLACK")
                  << " PLAYER IS IN STALEMATE (PAT).\n";
        utils::Logger::listener(str.str());
    }

    void CLIListener::on_player_disqualified(const board::Color color)
    {
        std::stringstream str;
        str << "THE " << (static_cast<bool>(color) ? "BLACK" : "WHITE")
                 << " PLAYER WAS DISQUALIFIED.\n";
        utils::Logger::listener(str.str());
    }

    void CLIListener::on_draw()
    {
        utils::Logger::listener("THE GAME IS A DRAW.\n");
    }
}
