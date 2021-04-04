#pragma once

#include "chessboard.hh"
#include "move.hh"

namespace board {
    class Rule {
    public:
        static std::vector<Move> generate_all_moves(const Chessboard& board);
        static std::vector<Move> generate_pawn_moves(const Chessboard& board);
        static std::vector<Move> generate_king_moves(const Chessboard& board);
        static std::vector<Move> generate_bishop_moves
            (const Chessboard& board);
        static std::vector<Move> generate_rook_moves(const Chessboard& board);
        static std::vector<Move> generate_queen_moves(const Chessboard& board);
        static std::vector<Move> generate_knight_moves
            (const Chessboard& board);

        static std::vector<Move>
        generate_all_captures(const Chessboard& board);

        static std::vector<Move>
        generate_pawn_captures(const Chessboard& board);

        static std::vector<Move>
        generate_king_captures(const Chessboard& board);

        static std::vector<Move>
        generate_bishop_captures(const Chessboard& board);

        static std::vector<Move>
        generate_rook_captures(const Chessboard& board);

        static std::vector<Move>
        generate_queen_captures(const Chessboard& board);

        static std::vector<Move>
        generate_knight_captures(const Chessboard& board);
    };
}
