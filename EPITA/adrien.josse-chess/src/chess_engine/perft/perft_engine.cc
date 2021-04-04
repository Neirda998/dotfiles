#include "perft_engine.hh"

namespace perft_engine
{
    int PerftEngine::rec_compute(board::Chessboard& board, int depth)
    {
        auto moves = board.generate_legal_moves();

        if (depth == 1)
            return moves.size();

        int res = 0;

        for (auto move : moves)
        {
            auto board_cpy = board::Chessboard(board);
            board_cpy.do_move(move, false);
            res += rec_compute(board_cpy, depth - 1);
        }

        return res;
    }

    int PerftEngine::compute(board::Chessboard& board, int depth)
    {
        if (depth == 0)
            return 1;
        return rec_compute(board, depth);
    }
}
