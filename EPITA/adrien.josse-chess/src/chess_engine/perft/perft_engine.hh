#include "chessboard.hh"

namespace perft_engine
{
    class PerftEngine
    {
    public:
        PerftEngine() {}

        int compute(board::Chessboard& board, int depth);

    private:
        int rec_compute(board::Chessboard& board, int depth);

    };
}
