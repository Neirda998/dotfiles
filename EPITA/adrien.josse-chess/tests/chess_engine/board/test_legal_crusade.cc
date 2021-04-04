#include <gtest/gtest.h>

#include "chessboard.hh"
#include "chessboard-representation.hh"
#include "rule.hh"

TEST(generate_legal_captures, game_start)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    for (int i = 0; i < 8; i++)
    {
        auto pawn = std::make_tuple(i, 1, 4);
        pieces.push_back(pawn);
    }

    //Rooks
    pieces.push_back(std::make_tuple(0, 0, 1));
    pieces.push_back(std::make_tuple(7, 0, 1));

    //Knights
    pieces.push_back(std::make_tuple(1, 0, 3));
    pieces.push_back(std::make_tuple(6, 0, 3));

    //Bishops
    pieces.push_back(std::make_tuple(2, 0, 2));
    pieces.push_back(std::make_tuple(5, 0, 2));

    //Queen
    pieces.push_back(std::make_tuple(3, 0, 0));

    //King
    pieces.push_back(std::make_tuple(4, 0, 5));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, true, true, true, true, 0);

    auto moves = board.generate_legal_captures();

    EXPECT_EQ(moves.size(), 0);
}

/*TEST(generate_legal_captures, check_move)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Queens
    pieces.push_back(std::make_tuple(3, 4, 8));
    pieces.push_back(std::make_tuple(5, 4, 8));

    //King
    pieces.push_back(std::make_tuple(4, 2, 5));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, false, false, false, false, 42);

    auto moves = board.generate_legal_moves();

    EXPECT_EQ(
        std::find(moves.begin(), moves.end(),
            board::Move(17179869184, 17179869184 * 2, board::PieceType::KING,
                std::nullopt, std::nullopt,
                false, false, false, false)),
            moves.end()
    );

    EXPECT_EQ(moves.size(), 5);
    }*/

TEST(generate_legal_captures, edwards_1)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //White Pawns
    pieces.push_back(std::make_tuple(0, 1, 4));
    pieces.push_back(std::make_tuple(1, 1, 4));
    pieces.push_back(std::make_tuple(2, 1, 4));
    pieces.push_back(std::make_tuple(6, 1, 4));
    pieces.push_back(std::make_tuple(7, 1, 4));
    pieces.push_back(std::make_tuple(3, 6, 4));

    //White Rooks
    pieces.push_back(std::make_tuple(0, 0, 1));
    pieces.push_back(std::make_tuple(7, 0, 1));

    //White Findus
    pieces.push_back(std::make_tuple(1, 0, 3));
    pieces.push_back(std::make_tuple(4, 1, 3));

    //White Bishops
    pieces.push_back(std::make_tuple(2, 0, 2));
    pieces.push_back(std::make_tuple(2, 3, 2));

    //White Queen
    pieces.push_back(std::make_tuple(3, 0, 0));

    //White King
    pieces.push_back(std::make_tuple(4, 0, 5));

    //Black Pawns
    pieces.push_back(std::make_tuple(0, 6, 10));
    pieces.push_back(std::make_tuple(1, 6, 10));
    pieces.push_back(std::make_tuple(2, 5, 10));
    pieces.push_back(std::make_tuple(5, 6, 10));
    pieces.push_back(std::make_tuple(6, 6, 10));
    pieces.push_back(std::make_tuple(7, 6, 10));

    //Black Rooks
    pieces.push_back(std::make_tuple(0, 7, 7));
    pieces.push_back(std::make_tuple(7, 7, 7));

    //Black Findus
    pieces.push_back(std::make_tuple(1, 7, 9));
    pieces.push_back(std::make_tuple(5, 1, 9));

    //Black Bishops
    pieces.push_back(std::make_tuple(2, 7, 8));
    pieces.push_back(std::make_tuple(4, 6, 8));

    //Black Queen
    pieces.push_back(std::make_tuple(3, 7, 6));

    //Black King
    pieces.push_back(std::make_tuple(5, 7, 11));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, true, true, true, true, 0);

    auto control = board::Rule::generate_all_captures(board);

    auto rook = board::Rule::generate_rook_captures(board);
    auto knight = board::Rule::generate_knight_captures(board);
    auto bishop = board::Rule::generate_bishop_captures(board);
    auto queen = board::Rule::generate_queen_captures(board);
    auto king = board::Rule::generate_king_captures(board);
    auto pawn = board::Rule::generate_pawn_captures(board);

    auto captures = board.generate_legal_captures();

    EXPECT_EQ(
        std::find(captures.begin(), captures.end(),
            board::Move(4294967296, 2199023255552, board::PieceType::KING,
                board::PieceType::KNIGHT, std::nullopt,
                false, false, false, false)),
            captures.end()
    );

    EXPECT_EQ(
        std::find(captures.begin(), captures.end(),
            board::Move(524288, 70368744177664, board::PieceType::BISHOP,
                board::PieceType::PAWN, std::nullopt,
                false, false, false, false)),
            captures.end()
    );

    EXPECT_EQ(rook.size(), 0);
    EXPECT_EQ(knight.size(), 0);
    EXPECT_EQ(bishop.size(), 1);
    EXPECT_EQ(queen.size(), 0);
    EXPECT_EQ(king.size(), 1);
    EXPECT_EQ(pawn.size(), 4);

    EXPECT_EQ(control.size(), 6);
    EXPECT_EQ(captures.size(), 6);
}
