#include <gtest/gtest.h>

#include <optional>
#include <vector>

#include "chessboard-representation.hh"

TEST(bitboard, default_constructor)
{
    auto rep = board::ChessboardRepresentation();

    std::string check = "8 r n b q k b n r \n"
                        "7 p p p p p p p p \n"
                        "6 . . . . . . . . \n"
                        "5 . . . . . . . . \n"
                        "4 . . . . . . . . \n"
                        "3 . . . . . . . . \n"
                        "2 P P P P P P P P \n"
                        "1 R N B Q K B N R \n"
                        "  A B C D E F G H \n";

    EXPECT_EQ(rep.generate_ascii_board(12), check);
}

TEST(bitboard, single_bitboard_white)
{
    auto rep = board::ChessboardRepresentation();

    std::string check = "8 . . . . . . . . \n"
                        "7 . . . . . . . . \n"
                        "6 . . . . . . . . \n"
                        "5 . . . . . . . . \n"
                        "4 . . . . . . . . \n"
                        "3 . . . . . . . . \n"
                        "2 . . . . . . . . \n"
                        "1 R . . . . . . R \n"
                        "  A B C D E F G H \n";

    EXPECT_EQ(rep.generate_ascii_board(1), check);
}

TEST(bitboard, single_bitboard_black)
{
    auto rep = board::ChessboardRepresentation();

    std::string check = "8 . . . . . . . . \n"
                        "7 p p p p p p p p \n"
                        "6 . . . . . . . . \n"
                        "5 . . . . . . . . \n"
                        "4 . . . . . . . . \n"
                        "3 . . . . . . . . \n"
                        "2 . . . . . . . . \n"
                        "1 . . . . . . . . \n"
                        "  A B C D E F G H \n";

    EXPECT_EQ(rep.generate_ascii_board(10), check);
}

TEST(bitboard, split_boards)
{
    auto rep = board::ChessboardRepresentation();

    std::vector<uint64_t> subs = rep.split_boards(1);

    uint64_t tmp = 1;

    EXPECT_EQ(subs.size(), 2);
    EXPECT_EQ(subs[0], 1);
    EXPECT_EQ(subs[1], tmp << 56);
}

TEST(bitboard, fen_constructor)
{
    auto tuple_vec = std::vector<std::tuple<size_t, size_t, size_t>>();

    auto rep = board::ChessboardRepresentation(tuple_vec);

    std::string check = "8 . . . . . . . . \n"
                        "7 . . . . . . . . \n"
                        "6 . . . . . . . . \n"
                        "5 . . . . . . . . \n"
                        "4 . . . . . . . . \n"
                        "3 . . . . . . . . \n"
                        "2 . . . . . . . . \n"
                        "1 . . . . . . . . \n"
                        "  A B C D E F G H \n";

    EXPECT_EQ(rep.generate_ascii_board(12), check);
}

TEST(bitboard, fen_constructor_rook)
{
    auto tuple_vec = std::vector<std::tuple<size_t, size_t, size_t>>();

    tuple_vec.push_back({0, 0, 1});
    tuple_vec.push_back({7, 0, 1});

    auto rep = board::ChessboardRepresentation(tuple_vec);

    std::string check = "8 . . . . . . . . \n"
                        "7 . . . . . . . . \n"
                        "6 . . . . . . . . \n"
                        "5 . . . . . . . . \n"
                        "4 . . . . . . . . \n"
                        "3 . . . . . . . . \n"
                        "2 . . . . . . . . \n"
                        "1 R . . . . . . R \n"
                        "  A B C D E F G H \n";

    EXPECT_EQ(rep.generate_ascii_board(12), check);
}

TEST(bitboard, fen_constructor_full_board)
{
    auto tuple_vec = std::vector<std::tuple<size_t, size_t, size_t>>();

    // rooks
    tuple_vec.push_back({0, 0, 1});
    tuple_vec.push_back({7, 0, 1});
    tuple_vec.push_back({0, 7, 7});
    tuple_vec.push_back({7, 7, 7});

    // knights
    tuple_vec.push_back({1, 0, 3});
    tuple_vec.push_back({6, 0, 3});
    tuple_vec.push_back({1, 7, 9});
    tuple_vec.push_back({6, 7, 9});

    // bishops
    tuple_vec.push_back({2, 0, 2});
    tuple_vec.push_back({5, 0, 2});
    tuple_vec.push_back({2, 7, 8});
    tuple_vec.push_back({5, 7, 8});

    //kings
    tuple_vec.push_back({4, 0, 5});
    tuple_vec.push_back({4, 7, 11});

    //queens
    tuple_vec.push_back({3, 0, 0});
    tuple_vec.push_back({3, 7, 6});

    // pawns
    tuple_vec.push_back({0, 1, 4});
    tuple_vec.push_back({1, 1, 4});
    tuple_vec.push_back({2, 1, 4});
    tuple_vec.push_back({3, 1, 4});
    tuple_vec.push_back({4, 1, 4});
    tuple_vec.push_back({5, 1, 4});
    tuple_vec.push_back({6, 1, 4});
    tuple_vec.push_back({7, 1, 4});
    tuple_vec.push_back({0, 6, 10});
    tuple_vec.push_back({1, 6, 10});
    tuple_vec.push_back({2, 6, 10});
    tuple_vec.push_back({3, 6, 10});
    tuple_vec.push_back({4, 6, 10});
    tuple_vec.push_back({5, 6, 10});
    tuple_vec.push_back({6, 6, 10});
    tuple_vec.push_back({7, 6, 10});

    auto rep = board::ChessboardRepresentation(tuple_vec);

    std::string check = "8 r n b q k b n r \n"
                        "7 p p p p p p p p \n"
                        "6 . . . . . . . . \n"
                        "5 . . . . . . . . \n"
                        "4 . . . . . . . . \n"
                        "3 . . . . . . . . \n"
                        "2 P P P P P P P P \n"
                        "1 R N B Q K B N R \n"
                        "  A B C D E F G H \n";

    EXPECT_EQ(rep.generate_ascii_board(12), check);
}
