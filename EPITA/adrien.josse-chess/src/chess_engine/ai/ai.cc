#include "ai.hh"
#include "minimax.hh"
#include "utils.hh"

#include <iostream>

namespace ai
{
    bool AI::endgame = false;

    int AI::evaluate(board::Chessboard& board)
    {
        if (board.is_checkmate())
            return board.white_turn_get() ? -9999 : 9999;
        if (board.is_draw())
            return 0;
        int value = 0;
        auto bitboards = board.rep_get().bitboards_get();
        int nb_queens = 0;
        for (size_t bit_idx = 0; bit_idx < 12; bit_idx++)
        {
            uint64_t idx = 1;
            for (int i = 1; i <= 64; ++i)
            {
                uint64_t bit_pos = bitboards.at(bit_idx) & idx;
                if (bit_pos)
                {
                    auto coords = board::get_coordinates(bit_pos);
                    bool white = bit_idx < 6;
                    int file = coords.first;
                    int rank = white ? 7 - coords.second : coords.second;

                    int d = white ? 1 : -1;

                    if (bit_idx % 6 == 0) // Queen
                    {
                        value += queen_pst[8 * rank + file] * d;
                        nb_queens++;
                    }
                    else if (bit_idx % 6 == 1) // Rook
                        value += rook_pst[8 * rank + file] * d;
                    else if (bit_idx % 6 == 2) // Bishop
                        value += bishop_pst[8 * rank + file] * d;
                    else if (bit_idx % 6 == 3) // Knights
                        value += knight_pst[8 * rank + file] * d;
                    else if (bit_idx % 6 == 4) // Pawn
                        value += pawn_pst[8 * rank + file] * d;
                    else if (bit_idx % 6 == 5) // King
                    {
                        if (AI::endgame)
                            value += king_pst_end[8 * rank + file] * d;
                        else
                            value += king_pst_mid[8 * rank + file] * d;
                    }

                    value += AI::values[bit_idx];
                }
                idx = idx << 1;
            }
            AI::endgame |= nb_queens;
        }
        return value;
    }

    board::Move AI::search(board::Chessboard& board)
    {
        return Minimax::search(board);
    }
}
