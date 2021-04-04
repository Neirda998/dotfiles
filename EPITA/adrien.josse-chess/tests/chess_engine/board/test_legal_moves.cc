#include <gtest/gtest.h>

#include "chessboard.hh"
#include "chessboard-representation.hh"
#include "rule.hh"

TEST(generate_legal_moves, game_start)
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

    auto moves = board.generate_legal_moves();

    EXPECT_EQ(moves.size(), 20);
}

TEST(generate_legal_moves, check_move)
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
}

TEST(generate_legal_moves, edwards_1)
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
    auto board = board::Chessboard(rep, true, true, true, false, false, 0);

    auto control = board::Rule::generate_all_moves(board);

    auto rook = board::Rule::generate_rook_moves(board);
    auto knight = board::Rule::generate_knight_moves(board);
    auto bishop = board::Rule::generate_bishop_moves(board);
    auto queen = board::Rule::generate_queen_moves(board);
    auto king = board::Rule::generate_king_moves(board);
    auto pawn = board::Rule::generate_pawn_moves(board);

    auto moves = board.generate_legal_moves();

    EXPECT_EQ(rook.size(), 2);
    EXPECT_EQ(knight.size(), 8);
    EXPECT_EQ(bishop.size(), 12);
    EXPECT_EQ(queen.size(), 5);
    EXPECT_EQ(king.size(), 4);
    EXPECT_EQ(pawn.size(), 13);

    EXPECT_EQ(control.size(), 44);
    EXPECT_EQ(moves.size(), 44);
}

TEST(generate_legal_moves, myo_pin_passant)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //White Pawns
    pieces.push_back(std::make_tuple(3, 4, 4));

    //White King
    pieces.push_back(std::make_tuple(0, 4, 5));

    //Black Pawns
    pieces.push_back(std::make_tuple(4, 4, 10));

    //Black Rook
    pieces.push_back(std::make_tuple(7, 4, 7));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, false, false, false, false, 666);

    board.en_passant_set(68719476736);

    auto control = board::Rule::generate_all_moves(board);

    auto rook = board::Rule::generate_rook_moves(board);
    auto knight = board::Rule::generate_knight_moves(board);
    auto bishop = board::Rule::generate_bishop_moves(board);
    auto queen = board::Rule::generate_queen_moves(board);
    auto king = board::Rule::generate_king_moves(board);
    auto pawn = board::Rule::generate_pawn_moves(board);

    auto moves = board.generate_legal_moves();

    EXPECT_EQ(rook.size(), 0);
    EXPECT_EQ(knight.size(), 0);
    EXPECT_EQ(bishop.size(), 0);
    EXPECT_EQ(queen.size(), 0);
    EXPECT_EQ(king.size(), 5);
    EXPECT_EQ(pawn.size(), 2);

    EXPECT_EQ(control.size(), 7);
    EXPECT_EQ(moves.size(), 6);
}

TEST(generate_legal_moves, king_crimson_castling)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //White Rook
    pieces.push_back(std::make_tuple(0, 0, 1));

    //White King Crimson
    pieces.push_back(std::make_tuple(4, 0, 5));

    //White Bishop
    pieces.push_back(std::make_tuple(2, 4, 2));

    //Black King Crimson
    pieces.push_back(std::make_tuple(4, 7, 11));

    //Black Rook
    pieces.push_back(std::make_tuple(7, 7, 7));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, false, false, true, false, 69);

    auto moves = board.generate_legal_moves();

    EXPECT_EQ(moves.size(), 12);
}

TEST(generate_legal_moves, queen_crimson_castling)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //White Rook
    pieces.push_back(std::make_tuple(0, 0, 1));

    //White King Crimson
    pieces.push_back(std::make_tuple(4, 0, 5));

    //White Bishop
    pieces.push_back(std::make_tuple(6, 4, 2));

    //Black King Crimson
    pieces.push_back(std::make_tuple(4, 7, 11));

    //Black Rook
    pieces.push_back(std::make_tuple(7, 0, 7));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, false, false, false, true, 69);

    auto moves = board.generate_legal_moves();

    EXPECT_EQ(moves.size(), 13);
}

TEST(generate_legal_moves, next_level_strats)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //White Pawns
    pieces.push_back(std::make_tuple(0, 6, 4));

    //Black Rook
    pieces.push_back(std::make_tuple(0, 7, 7));
    pieces.push_back(std::make_tuple(7, 7, 7)); // JACKPOT

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, false, false, false, false, 666);

    auto pawn = board::Rule::generate_pawn_moves(board);

    auto moves = board.generate_legal_moves();

    EXPECT_EQ(pawn.size(), 0);

    EXPECT_EQ(moves.size(), 0);
}
