#include <gtest/gtest.h>

#include "chessboard.hh"
#include "chessboard-representation.hh"
#include "rule.hh"

TEST(move_generation, single_white_pawn_moves)
{
    auto pawn = std::make_tuple(2, 1, 4);
    auto knight = std::make_tuple(3, 2, 9);
    auto queen = std::make_tuple(1, 2, 0);
    std::vector<std::tuple<size_t, size_t, size_t>> pieces = { pawn, knight, queen };

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, false, false, false, false, 0);
    auto moves = board::Rule::generate_pawn_moves(board);

    EXPECT_NE(
        std::find(moves.begin(), moves.end(),
            board::Move(131072, 262144, board::PieceType::PAWN,
                std::nullopt, std::nullopt,
                false, false, false, false)),
            moves.end()
    );

    EXPECT_NE(
        std::find(moves.begin(), moves.end(),
            board::Move(131072, 524288, board::PieceType::PAWN,
                std::nullopt, std::nullopt,
                true, false, false, false)),
            moves.end()
    );

    EXPECT_NE(
        std::find(moves.begin(), moves.end(),
            board::Move(131072, 131072 * 512, board::PieceType::PAWN,
                std::nullopt, board::PieceType::KNIGHT,
                false, false, false, false)),
            moves.end()
    );

    EXPECT_EQ(moves.size(), 3);
}

TEST(move_generation, multiple_black_pawn_moves)
{
    auto pawn1 = std::make_tuple(4, 4, 10);
    auto pawn2 = std::make_tuple(0, 1, 10);
    auto pawn3 = std::make_tuple(6, 3, 10);
    auto pawn4 = std::make_tuple(5, 3, 4);
    auto pawn5 = std::make_tuple(7, 3, 4);
    std::vector<std::tuple<size_t, size_t, size_t>> pieces = { pawn1, pawn2, pawn3, pawn4, pawn5 };

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, false, false, false, false, 69);
    board.en_passant_set(2251799813685248 * 256);
    auto moves = board::Rule::generate_pawn_moves(board);

    // First Pawn: 2 moves
    EXPECT_NE(
        std::find(moves.begin(), moves.end(),
            board::Move(68719476736, 34359738368, board::PieceType::PAWN,
                std::nullopt, std::nullopt,
                false, false, false, false)),
            moves.end()
    );

    EXPECT_NE(
        std::find(moves.begin(), moves.end(),
            board::Move(68719476736, 68719476736 * 128, board::PieceType::PAWN,
                std::nullopt, board::PieceType::PAWN,
                false, false, false, false)),
            moves.end()
    );

    //Second Pawn: 4 move
    for (size_t i = 0; i < 4; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(2, 1, board::PieceType::PAWN,
                    board::piecetype_array[i], std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
    }

    //Third Pawn: 2 moves
    EXPECT_NE(
        std::find(moves.begin(), moves.end(),
            board::Move(2251799813685248, 1125899906842624, board::PieceType::PAWN,
                std::nullopt, std::nullopt,
                false, false, false, false)),
            moves.end()
    );

    EXPECT_NE(
        std::find(moves.begin(), moves.end(),
            board::Move(2251799813685248, 2251799813685248 * 128, board::PieceType::PAWN,
                std::nullopt, board::PieceType::PAWN,
                false, false, false, true)),
            moves.end()
    );

    EXPECT_EQ(moves.size(), 8);
}

TEST(move_generation, white_king)
{
    auto king = std::make_tuple(3, 4, 5);
    std::vector<std::tuple<size_t, size_t, size_t>> pieces = { king };

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, false, false, false, false, 42);
    auto moves = board::Rule::generate_king_moves(board);

    std::vector<uint64_t> input = { 536870912, 134217728, 1048576, 68719476736,
                                    524288, 34359738368, 137438953472, 2097152 };

    for (size_t i = 0; i < input.size(); i++)
    {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(268435456, input[i], board::PieceType::KING,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
    }

    EXPECT_EQ(moves.size(), 8);
}

TEST(move_generation, black_king_castling)
{
    auto king = std::make_tuple(4, 7, 11);
    std::vector<std::tuple<size_t, size_t, size_t>> pieces = { king };

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, true, true, true, true, 1);
    auto moves = board::Rule::generate_king_moves(board);

    std::vector<uint64_t> input = { 2147483648, 140737488355328, 1073741824,
                                    70368744177664, 274877906944 };

    for (size_t i = 0; i < input.size(); i++)
    {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(549755813888, input[i], board::PieceType::KING,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
    }

    EXPECT_NE(
        std::find(moves.begin(), moves.end(),
            board::Move(549755813888, 549755813888 * 65536, board::PieceType::KING,
                std::nullopt, std::nullopt,
                false, true, false, false)),
            moves.end()
    );

    EXPECT_NE(
        std::find(moves.begin(), moves.end(),
            board::Move(549755813888, 549755813888 / 65536, board::PieceType::KING,
                std::nullopt, std::nullopt,
                false, false, true, false)),
            moves.end()
    );

    EXPECT_EQ(moves.size(), 7);
}

TEST(move_generation, white_queen) {
    auto queen = std::make_tuple(4, 5, 0);
    std::vector<std::tuple<size_t, size_t, size_t>> pieces = { queen };

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, false, false, false, true, 66);
    auto moves = board::Rule::generate_queen_moves(board);

    uint64_t init_pos = 137438953472;
    uint64_t dest = init_pos * 256;

    for (size_t i = 0; i < 3; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest *= 256;
    }

    dest = init_pos * 512;

    for (size_t i = 0; i < 2; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest *= 512;
    }

    dest = init_pos * 2;

    for (size_t i = 0; i < 2; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest *= 2;
    }

    dest = init_pos / 128;

    for (size_t i = 0; i < 2; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest /= 128;
    }

    dest = init_pos / 256;

    for (size_t i = 0; i < 4; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest /= 256;
    }

    dest = init_pos / 512;

    for (size_t i = 0; i < 4; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest /= 512;
    }

    dest = init_pos / 2;

    for (size_t i = 0; i < 5; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest /= 2;
    }

    dest = init_pos * 128;

    for (size_t i = 0; i < 3; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest *= 128;
    }

    EXPECT_EQ(moves.size(), 25);
}

TEST(move_generation, black_queens) {
    auto queen = std::make_tuple(4, 5, 6);
    auto queen2 = std::make_tuple(0, 0, 6);
    std::vector<std::tuple<size_t, size_t, size_t>> pieces = { queen, queen2 };

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, false, true, true, false, 25);
    auto moves = board::Rule::generate_queen_moves(board);

    uint64_t init_pos = 137438953472;
    uint64_t dest = init_pos * 256;

    for (size_t i = 0; i < 3; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest *= 256;
    }

    dest = init_pos * 512;

    for (size_t i = 0; i < 2; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest *= 512;
    }

    dest = init_pos * 2;

    for (size_t i = 0; i < 2; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest *= 2;
    }

    dest = init_pos / 128;

    for (size_t i = 0; i < 2; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest /= 128;
    }

    dest = init_pos / 256;

    for (size_t i = 0; i < 4; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest /= 256;
    }

    dest = init_pos / 512;

    for (size_t i = 0; i < 4; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest /= 512;
    }

    dest = init_pos / 2;

    for (size_t i = 0; i < 5; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest /= 2;
    }

    dest = init_pos * 128;

    for (size_t i = 0; i < 3; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest *= 128;
    }

    init_pos = 1;
    dest = init_pos * 256;

    for (size_t i = 0; i < 7; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest *= 256;
    }

    dest = init_pos * 512;

    for (size_t i = 0; i < 7; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest *= 512;
    }

    dest = init_pos * 2;

    for (size_t i = 0; i < 7; i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(init_pos, dest, board::PieceType::QUEEN,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
        dest *= 2;
    }

    EXPECT_EQ(moves.size(), 46);
}

TEST(move_generation, white_knight) {
    auto knight = std::make_tuple(3, 4, 3);
    std::vector<std::tuple<size_t, size_t, size_t>> pieces = { knight };

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, false, false, false, false, 42);
    auto moves = board::Rule::generate_knight_moves(board);

    std::vector<uint64_t> input = { 4194304, 8192, 2048, 262144,
                                    17179869184, 8796093022208,
                                    35184372088832, 274877906944 };

    for (size_t i = 0; i < input.size(); i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(268435456, input[i], board::PieceType::KNIGHT,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
    }

    EXPECT_EQ(moves.size(), 8);
}

TEST(move_generation, dark_knights) {
    auto hollow = std::make_tuple(3, 4, 9);
    auto knight = std::make_tuple(0, 7, 9);
    std::vector<std::tuple<size_t, size_t, size_t>> pieces = { hollow, knight };

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, false, false, false, false, 4577);
    auto moves = board::Rule::generate_knight_moves(board);

    std::vector<uint64_t> input = { 4194304, 8192, 2048, 262144,
                                    17179869184, 8796093022208,
                                    35184372088832, 274877906944 };

    for (size_t i = 0; i < input.size(); i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(268435456, input[i], board::PieceType::KNIGHT,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
    }

    std::vector<uint64_t> inpute = { 8192, 4194304 };

    for (size_t i = 0; i < inpute.size(); i++) {
        EXPECT_NE(
            std::find(moves.begin(), moves.end(),
                board::Move(128, inpute[i], board::PieceType::KNIGHT,
                    std::nullopt, std::nullopt,
                    false, false, false, false)),
                moves.end()
        );
    }

    EXPECT_EQ(moves.size(), 10);
}

TEST(move_generation, half_chessboard_white_turn)
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

    auto rook_moves = board::Rule::generate_rook_moves(board);
    auto knight_moves = board::Rule::generate_knight_moves(board);
    auto bishop_moves = board::Rule::generate_bishop_moves(board);
    auto queen_moves = board::Rule::generate_queen_moves(board);
    auto king_moves = board::Rule::generate_king_moves(board);
    auto pawn_moves = board::Rule::generate_pawn_moves(board);

    EXPECT_EQ(rook_moves.size(), 0);
    EXPECT_EQ(knight_moves.size(), 4);
    EXPECT_EQ(bishop_moves.size(), 0);
    EXPECT_EQ(queen_moves.size(), 0);
    EXPECT_EQ(king_moves.size(), 0);
    EXPECT_EQ(pawn_moves.size(), 16);
}

TEST(check, pawn_threat_white)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //King
    pieces.push_back(std::make_tuple(3, 5, 5));

    //Pawn
    pieces.push_back(std::make_tuple(4, 6, 10));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, false, false, false, false, 666);

    EXPECT_EQ(board.pawn_threat(true), true);
    EXPECT_EQ(board.pawn_threat(false), false);
}

TEST(check, pawn_no_threat_black)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //King
    pieces.push_back(std::make_tuple(3, 5, 11));

    //Pawn
    pieces.push_back(std::make_tuple(4, 6, 10));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, false, false, false, false, 665);

    EXPECT_EQ(board.pawn_threat(false), false);
}

TEST(check, knight_threat_white)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //King
    pieces.push_back(std::make_tuple(7, 7, 5));

    //Knight
    pieces.push_back(std::make_tuple(5, 6, 9));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, false, false, false, false, 666);

    EXPECT_EQ(board.knight_threat(true), true);
    EXPECT_EQ(board.knight_threat(false), false);
}

TEST(check, queen_threat_black)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //King
    pieces.push_back(std::make_tuple(0, 0, 11));

    //Queen
    pieces.push_back(std::make_tuple(7, 7, 0));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, false, false, false, false, 69);

    EXPECT_EQ(board.queen_threat(false), true);
}

TEST(check, queen_no_threat_black)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //King
    pieces.push_back(std::make_tuple(0, 0, 11));

    //Queen
    pieces.push_back(std::make_tuple(7, 7, 0));

    //Pawn
    pieces.push_back(std::make_tuple(5, 5, 4));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, false, false, false, false, false, 69);

    EXPECT_EQ(board.queen_threat(false), false);
}

TEST(check, check_white)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //White King
    pieces.push_back(std::make_tuple(7, 0, 5));

    //Black Rook
    pieces.push_back(std::make_tuple(5, 0, 7));

    //Black King
    pieces.push_back(std::make_tuple(5, 1, 11));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, false, false, false, false, 42);

    EXPECT_EQ(board.is_check(), true);
}

TEST(check, checkmate_white)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //White King
    pieces.push_back(std::make_tuple(0, 0, 5));

    //Black Queens
    pieces.push_back(std::make_tuple(1, 0, 6));
    pieces.push_back(std::make_tuple(0, 1, 6));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, false, false, false, false, 42);

    EXPECT_EQ(board.is_checkmate(), true);
}

TEST(check, simple_stalemate_white)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //White King
    pieces.push_back(std::make_tuple(7, 0, 5));

    //Black Rook
    pieces.push_back(std::make_tuple(5, 1, 7));

    //Black King
    pieces.push_back(std::make_tuple(5, 0, 11));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, false, false, false, false, 42);

    EXPECT_EQ(board.is_stalemate(), true);
}

TEST(check, middle_stalemate_white)
{
    std::vector<std::tuple<size_t, size_t, size_t>> pieces;

    //White King
    pieces.push_back(std::make_tuple(7, 0, 5));

    //Black Knight
    pieces.push_back(std::make_tuple(5, 2, 9));

    //Black Bishop
    pieces.push_back(std::make_tuple(5, 0, 8));

    auto rep = board::ChessboardRepresentation(pieces);
    auto board = board::Chessboard(rep, true, false, false, false, false, 42);

    EXPECT_EQ(board.is_stalemate(), true);
}
