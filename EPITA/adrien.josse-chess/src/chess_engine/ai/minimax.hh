#pragma once

#include <chrono>

namespace ai
{
    class Minimax
    {
    public:
        Minimax() {}

        static board::Move search(board::Chessboard& board);

    private:
        static int quiesce(board::Chessboard& board, int alpha, int beta,
                int depth, std::chrono::milliseconds end_time);
        static int min(board::Chessboard& board, int depth, int alpha,
                       int beta, std::chrono::milliseconds end_time);
        static int max(board::Chessboard& board, int depth, int alpha,
                       int beta, std::chrono::milliseconds end_time);
        static int maxMC(board::Chessboard& board, int depth);
        static int minMC(board::Chessboard& board, int depth);
    };
}
