#include <gtest/gtest.h>

#include "chessboard.hh"

#define A1 1

#define A8 128

#define H1 (1ULL << 56)

#define H8 (1ULL << 63)

#define E1 (1ULL << 32)

#define E8 (1ULL << 39)

#define G1 (1ULL << 48)

#define G8 (1ULL << 55)

#define C1 (1ULL << 16)

#define C8 (1ULL << 23)

TEST(castling, king_move_wk)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Rook
    pieces.push_back(std::make_tuple(0, 0, 1));
    pieces.push_back(std::make_tuple(7, 0, 1));

    //King
    pieces.push_back(std::make_tuple(4, 0, 5));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, true, true, true, true, 42);

    auto moves = board.generate_legal_moves();
    auto castle = board::Move(E1, G1,
                    board::PieceType::KING,
                    std::nullopt, std::nullopt,
                    false, true, false, false);

    EXPECT_NE(
        std::find(moves.begin(), moves.end(), castle), moves.end()
    );

    board.do_move(castle, false);

    EXPECT_EQ(board.white_king_castling_get(), false);
    EXPECT_EQ(board.white_queen_castling_get(), false);
    EXPECT_EQ(board.black_king_castling_get(), true);
    EXPECT_EQ(board.black_queen_castling_get(), true);
}

TEST(castling, king_move_wq)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Rook
    pieces.push_back(std::make_tuple(0, 0, 1));
    pieces.push_back(std::make_tuple(7, 0, 1));

    //King
    pieces.push_back(std::make_tuple(4, 0, 5));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, true, true, true, true, 42);

    auto moves = board.generate_legal_moves();
    auto castle = board::Move(E1, C1,
                    board::PieceType::KING,
                    std::nullopt, std::nullopt,
                    false, false, true, false);

    EXPECT_NE(
        std::find(moves.begin(), moves.end(), castle), moves.end()
    );

    board.do_move(castle, false);

    EXPECT_EQ(board.white_king_castling_get(), false);
    EXPECT_EQ(board.white_queen_castling_get(), false);
    EXPECT_EQ(board.black_king_castling_get(), true);
    EXPECT_EQ(board.black_queen_castling_get(), true);
}

TEST(castling, king_move_bk)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Rook
    pieces.push_back(std::make_tuple(0, 7, 7));
    pieces.push_back(std::make_tuple(7, 7, 7));

    //King
    pieces.push_back(std::make_tuple(4, 7, 11));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, true, true, true, true, 43);

    auto moves = board.generate_legal_moves();
    auto castle = board::Move(E8, G8,
                    board::PieceType::KING,
                    std::nullopt, std::nullopt,
                    false, true, false, false);

    EXPECT_NE(
        std::find(moves.begin(), moves.end(), castle), moves.end()
    );

    board.do_move(castle, false);

    EXPECT_EQ(board.white_king_castling_get(), true);
    EXPECT_EQ(board.white_queen_castling_get(), true);
    EXPECT_EQ(board.black_king_castling_get(), false);
    EXPECT_EQ(board.black_queen_castling_get(), false);
}

TEST(castling, king_move_bq)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Rook
    pieces.push_back(std::make_tuple(0, 7, 7));
    pieces.push_back(std::make_tuple(7, 7, 7));

    //King
    pieces.push_back(std::make_tuple(4, 7, 11));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, true, true, true, true, 43);

    auto moves = board.generate_legal_moves();
    auto castle = board::Move(E8, C8,
                    board::PieceType::KING,
                    std::nullopt, std::nullopt,
                    false, false, true, false);

    EXPECT_NE(
        std::find(moves.begin(), moves.end(), castle), moves.end()
    );

    board.do_move(castle, false);

    EXPECT_EQ(board.white_king_castling_get(), true);
    EXPECT_EQ(board.white_queen_castling_get(), true);
    EXPECT_EQ(board.black_king_castling_get(), false);
    EXPECT_EQ(board.black_queen_castling_get(), false);
}

TEST(castling, rook_move_wk)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Rook
    pieces.push_back(std::make_tuple(0, 0, 1));
    pieces.push_back(std::make_tuple(7, 0, 1));

    //King
    pieces.push_back(std::make_tuple(4, 0, 5));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, true, true, true, true, 42);

    auto moves = board.generate_legal_moves();
    auto move = board::Move(H1, H1 * 2,
                    board::PieceType::ROOK,
                    std::nullopt, std::nullopt,
                    false, false, false, false);

    EXPECT_NE(
        std::find(moves.begin(), moves.end(), move), moves.end()
    );

    board.do_move(move, false);

    EXPECT_EQ(board.white_king_castling_get(), false);
    EXPECT_EQ(board.white_queen_castling_get(), true);
    EXPECT_EQ(board.black_king_castling_get(), true);
    EXPECT_EQ(board.black_queen_castling_get(), true);
}

TEST(castling, rook_move_wq)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Rook
    pieces.push_back(std::make_tuple(0, 0, 1));
    pieces.push_back(std::make_tuple(7, 0, 1));

    //King
    pieces.push_back(std::make_tuple(4, 0, 5));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, true, true, true, true, 42);

    auto moves = board.generate_legal_moves();
    auto move = board::Move(A1, A1 * 2,
                    board::PieceType::ROOK,
                    std::nullopt, std::nullopt,
                    false, false, false, false);

    EXPECT_NE(
        std::find(moves.begin(), moves.end(), move), moves.end()
    );

    board.do_move(move, false);

    EXPECT_EQ(board.white_king_castling_get(), true);
    EXPECT_EQ(board.white_queen_castling_get(), false);
    EXPECT_EQ(board.black_king_castling_get(), true);
    EXPECT_EQ(board.black_queen_castling_get(), true);
}

TEST(castling, rook_move_bk)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Rook
    pieces.push_back(std::make_tuple(0, 7, 7));
    pieces.push_back(std::make_tuple(7, 7, 7));

    //King
    pieces.push_back(std::make_tuple(4, 7, 11));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, true, true, true, true, 43);

    auto moves = board.generate_legal_moves();
    auto move = board::Move(H8, H8 / 2,
                    board::PieceType::ROOK,
                    std::nullopt, std::nullopt,
                    false, false, false, false);

    EXPECT_NE(
        std::find(moves.begin(), moves.end(), move), moves.end()
    );

    board.do_move(move, false);

    EXPECT_EQ(board.white_king_castling_get(), true);
    EXPECT_EQ(board.white_queen_castling_get(), true);
    EXPECT_EQ(board.black_king_castling_get(), false);
    EXPECT_EQ(board.black_queen_castling_get(), true);
}

TEST(castling, rook_move_bq)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Rook
    pieces.push_back(std::make_tuple(0, 7, 7));
    pieces.push_back(std::make_tuple(7, 7, 7));

    //King
    pieces.push_back(std::make_tuple(4, 7, 11));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, true, true, true, true, 43);

    auto moves = board.generate_legal_moves();
    auto move = board::Move(A8, A8 / 2,
                    board::PieceType::ROOK,
                    std::nullopt, std::nullopt,
                    false, false, false, false);

    EXPECT_NE(
        std::find(moves.begin(), moves.end(), move), moves.end()
    );

    board.do_move(move, false);

    EXPECT_EQ(board.white_king_castling_get(), true);
    EXPECT_EQ(board.white_queen_castling_get(), true);
    EXPECT_EQ(board.black_king_castling_get(), true);
    EXPECT_EQ(board.black_queen_castling_get(), false);
}

TEST(castling, rook_captured_wk)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Queen
    pieces.push_back(std::make_tuple(7, 1, 6));

    //Rook
    pieces.push_back(std::make_tuple(0, 0, 1));
    pieces.push_back(std::make_tuple(7, 0, 1));

    //King
    pieces.push_back(std::make_tuple(4, 0, 5));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, true, true, true, true, 43);

    auto moves = board.generate_legal_moves();
    auto move = board::Move(H1 * 2, H1,
                    board::PieceType::QUEEN,
                    std::nullopt, board::PieceType::ROOK,
                    false, false, false, false);

    EXPECT_NE(
        std::find(moves.begin(), moves.end(), move), moves.end()
    );

    board.do_move(move, false);

    EXPECT_EQ(board.white_king_castling_get(), false);
    EXPECT_EQ(board.white_queen_castling_get(), true);
    EXPECT_EQ(board.black_king_castling_get(), true);
    EXPECT_EQ(board.black_queen_castling_get(), true);
}

TEST(castling, rook_captured_wq)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Queen
    pieces.push_back(std::make_tuple(0, 1, 6));

    //Rook
    pieces.push_back(std::make_tuple(0, 0, 1));
    pieces.push_back(std::make_tuple(7, 0, 1));

    //King
    pieces.push_back(std::make_tuple(4, 0, 5));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, true, true, true, true, 43);

    auto moves = board.generate_legal_moves();
    auto move = board::Move(A1 * 2, A1,
                    board::PieceType::QUEEN,
                    std::nullopt, board::PieceType::ROOK,
                    false, false, false, false);

    EXPECT_NE(
        std::find(moves.begin(), moves.end(), move), moves.end()
    );

    board.do_move(move, false);

    EXPECT_EQ(board.white_king_castling_get(), true);
    EXPECT_EQ(board.white_queen_castling_get(), false);
    EXPECT_EQ(board.black_king_castling_get(), true);
    EXPECT_EQ(board.black_queen_castling_get(), true);
}

TEST(castling, rook_captured_bk)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Queen
    pieces.push_back(std::make_tuple(7, 6, 0));

    //Rook
    pieces.push_back(std::make_tuple(0, 7, 7));
    pieces.push_back(std::make_tuple(7, 7, 7));

    //King
    pieces.push_back(std::make_tuple(4, 7, 11));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, true, true, true, true, 42);

    auto moves = board.generate_legal_moves();
    auto move = board::Move(H8 / 2, H8,
                    board::PieceType::QUEEN,
                    std::nullopt, board::PieceType::ROOK,
                    false, false, false, false);

    EXPECT_NE(
        std::find(moves.begin(), moves.end(), move), moves.end()
    );

    board.do_move(move, false);

    EXPECT_EQ(board.white_king_castling_get(), true);
    EXPECT_EQ(board.white_queen_castling_get(), true);
    EXPECT_EQ(board.black_king_castling_get(), false);
    EXPECT_EQ(board.black_queen_castling_get(), true);
}

TEST(castling, rook_captured_bq)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Queen
    pieces.push_back(std::make_tuple(0, 6, 0));

    //Rook
    pieces.push_back(std::make_tuple(0, 7, 7));
    pieces.push_back(std::make_tuple(7, 7, 7));

    //King
    pieces.push_back(std::make_tuple(4, 7, 11));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, true, true, true, true, 42);

    auto moves = board.generate_legal_moves();
    auto move = board::Move(A8 / 2, A8,
                    board::PieceType::QUEEN,
                    std::nullopt, board::PieceType::ROOK,
                    false, false, false, false);

    EXPECT_NE(
        std::find(moves.begin(), moves.end(), move), moves.end()
    );

    board.do_move(move, false);

    EXPECT_EQ(board.white_king_castling_get(), true);
    EXPECT_EQ(board.white_queen_castling_get(), true);
    EXPECT_EQ(board.black_king_castling_get(), true);
    EXPECT_EQ(board.black_queen_castling_get(), false);
}

TEST(castling, bk_cannot_castle)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Bishop
    pieces.push_back(std::make_tuple(4, 6, 2));

    //Rook
    pieces.push_back(std::make_tuple(0, 7, 7));
    pieces.push_back(std::make_tuple(7, 7, 7));

    //King
    pieces.push_back(std::make_tuple(4, 7, 11));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, true, true, true, true, 43);

    auto moves = board.generate_legal_moves();
    auto king_castle = board::Move(E8, G8,
                    board::PieceType::KING,
                    std::nullopt, std::nullopt,
                    false, true, false, false);

    auto queen_castle = board::Move(E8, C8,
                    board::PieceType::KING,
                    std::nullopt, std::nullopt,
                    false, false, true, false);

    EXPECT_EQ(
        std::find(moves.begin(), moves.end(), queen_castle), moves.end()
    );

    EXPECT_EQ(
        std::find(moves.begin(), moves.end(), king_castle), moves.end()
    );
}

TEST(castling, bk_cannot_castle_2)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Bishop
    pieces.push_back(std::make_tuple(4, 5, 2));

    //Rook
    pieces.push_back(std::make_tuple(0, 7, 7));
    pieces.push_back(std::make_tuple(7, 7, 7));

    //King
    pieces.push_back(std::make_tuple(4, 7, 11));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, true, true, true, true, 43);

    auto moves = board.generate_legal_moves();
    auto king_castle = board::Move(E8, G8,
                    board::PieceType::KING,
                    std::nullopt, std::nullopt,
                    false, true, false, false);

    auto queen_castle = board::Move(E8, C8,
                    board::PieceType::KING,
                    std::nullopt, std::nullopt,
                    false, false, true, false);

    EXPECT_EQ(
        std::find(moves.begin(), moves.end(), queen_castle), moves.end()
    );

    EXPECT_EQ(
        std::find(moves.begin(), moves.end(), king_castle), moves.end()
    );
}

TEST(castling, wk_cannot_castle)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Bishop
    pieces.push_back(std::make_tuple(4, 1, 8));

    //Rook
    pieces.push_back(std::make_tuple(0, 0, 1));
    pieces.push_back(std::make_tuple(7, 0, 1));

    //King
    pieces.push_back(std::make_tuple(4, 0, 5));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, true, true, true, true, 42);

    auto moves = board.generate_legal_moves();
    auto king_castle = board::Move(E1, G1,
                    board::PieceType::KING,
                    std::nullopt, std::nullopt,
                    false, true, false, false);

    auto queen_castle = board::Move(E1, C1,
                    board::PieceType::KING,
                    std::nullopt, std::nullopt,
                    false, false, true, false);

    EXPECT_EQ(
        std::find(moves.begin(), moves.end(), queen_castle), moves.end()
    );

    EXPECT_EQ(
        std::find(moves.begin(), moves.end(), king_castle), moves.end()
    );
}

TEST(castling, wk_cannot_castle_2)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //Bishop
    pieces.push_back(std::make_tuple(4, 2, 8));

    //Rook
    pieces.push_back(std::make_tuple(0, 0, 1));
    pieces.push_back(std::make_tuple(7, 0, 1));

    //King
    pieces.push_back(std::make_tuple(4, 0, 5));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, true, true, true, true, 42);

    auto moves = board.generate_legal_moves();
    auto king_castle = board::Move(E1, G1,
                    board::PieceType::KING,
                    std::nullopt, std::nullopt,
                    false, true, false, false);

    auto queen_castle = board::Move(E1, C1,
                    board::PieceType::KING,
                    std::nullopt, std::nullopt,
                    false, false, true, false);

    EXPECT_EQ(
        std::find(moves.begin(), moves.end(), queen_castle), moves.end()
    );

    EXPECT_EQ(
        std::find(moves.begin(), moves.end(), king_castle), moves.end()
    );
}
