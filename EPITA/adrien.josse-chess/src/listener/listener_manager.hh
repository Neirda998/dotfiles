#pragma once

#include <vector>
#include <optional>

#include "chessboard.hh"
#include "listener.hh"
#include "pgn-move.hh"

namespace listener
{
    class ListenerManager
    {
    public:
        ListenerManager(std::vector<std::string> filenames,
                        board::Chessboard& board);

        void play(const std::vector<board::PgnMove>& pgn_moves, bool is_pgn);

        void close_listeners();

        void register_board(const board::ChessboardInterface& board_interface);
        void on_game_finished();
        void on_piece_moved(const board::PieceType piece,
                            const board::Position& from,
                            const board::Position& to);
        void on_piece_taken(const board::PieceType piece,
                            const board::Position& at);
        void on_piece_promoted(const board::PieceType piece,
                               const board::Position& at);
        void on_kingside_castling(const board::Color color);
        void on_queenside_castling(const board::Color color);
        void on_player_check(const board::Color color);
        void on_player_mat(const board::Color color);
        void on_player_pat(const board::Color color);
        void on_player_disqualified(const board::Color color);
        void on_draw();


    private:

        board::Move get_move(const std::optional<board::PgnMove>& pgn_move);
        void signal_move(const board::Move& move, bool is_ai);
        bool signal_board_state();

        std::vector<Listener*> listeners_;
        std::vector<void*> handles_;
        board::Chessboard board_;
    };
}
