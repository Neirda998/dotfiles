#include <gtest/gtest.h>

#include "ai.hh"
#include "chessboard.hh"
#include "chessboard-representation.hh"

TEST(eval, single_pawn)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    // White Pawn
    pieces.push_back(std::make_tuple(0, 1, 4));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, false, false, false, false, 0);

    EXPECT_EQ(ai::AI::evaluate(board), 105);
}

TEST(eval, six_pieces)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    // White King, Bishop, Pawn
    pieces.push_back(std::make_tuple(4, 6, 5));
    pieces.push_back(std::make_tuple(2, 0, 2));
    pieces.push_back(std::make_tuple(6, 6, 4));

    // Black Queen, Knight, Rook
    pieces.push_back(std::make_tuple(2, 7, 6));
    pieces.push_back(std::make_tuple(3, 3, 9));
    pieces.push_back(std::make_tuple(7, 7, 7));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, false, false, false, false, 0);

    int eval = (9000 - 50) + (320 - 10) + (100 + 50)
               - (900 - 10) - (300 + 20) - (500 + 0);
    EXPECT_EQ(ai::AI::evaluate(board), eval);
}

TEST(eval, black_king)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    // Black King
    pieces.push_back(std::make_tuple(3, 6, 11));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, false, false, false, false, 0);

    EXPECT_EQ(ai::AI::evaluate(board), -9000);
}
