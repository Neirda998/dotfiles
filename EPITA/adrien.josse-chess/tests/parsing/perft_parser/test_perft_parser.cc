#include <gtest/gtest.h>

#include "perft_parser.hh"

namespace parsing {

    TEST(perft_parser, rank_empty_rank) {

        std::string str_rank = "8";

        auto parser = PerftParser();
        auto rank = parser.parse_rank(str_rank);

        EXPECT_EQ(rank[board::File::A], std::nullopt);
        EXPECT_EQ(rank[board::File::B], std::nullopt);
        EXPECT_EQ(rank[board::File::C], std::nullopt);
        EXPECT_EQ(rank[board::File::D], std::nullopt);
        EXPECT_EQ(rank[board::File::E], std::nullopt);
        EXPECT_EQ(rank[board::File::F], std::nullopt);
        EXPECT_EQ(rank[board::File::G], std::nullopt);
        EXPECT_EQ(rank[board::File::H], std::nullopt);
    }

    TEST(perft_parser, rank_some_pieces) {

        std::string str_rank = "1RnBqKp1";

        auto parser = PerftParser();
        auto rank = parser.parse_rank(str_rank);

        EXPECT_EQ(rank[board::File::A], std::nullopt);
        auto pair_1 = std::make_pair<board::PieceType, board::Color>
                           (board::PieceType::ROOK, board::Color::WHITE);
        EXPECT_EQ(rank[board::File::B], pair_1);
        auto pair_2 = std::make_pair<board::PieceType, board::Color>
                           (board::PieceType::KNIGHT, board::Color::BLACK);
        EXPECT_EQ(rank[board::File::C], pair_2);
        auto pair_3 = std::make_pair<board::PieceType, board::Color>
                           (board::PieceType::BISHOP, board::Color::WHITE);
        EXPECT_EQ(rank[board::File::D], pair_3);
        auto pair_4 = std::make_pair<board::PieceType, board::Color>
                           (board::PieceType::QUEEN, board::Color::BLACK);
        EXPECT_EQ(rank[board::File::E], pair_4);
        auto pair_5 = std::make_pair<board::PieceType, board::Color>
                           (board::PieceType::KING, board::Color::WHITE);
        EXPECT_EQ(rank[board::File::F], pair_5);
        auto pair_6 = std::make_pair<board::PieceType, board::Color>
                           (board::PieceType::PAWN, board::Color::BLACK);
        EXPECT_EQ(rank[board::File::G], pair_6);
        EXPECT_EQ(rank[board::File::H], std::nullopt);
    }

    TEST(perft_parser, perft_short_line) {

        std::string str_perft = "../tests/custom_perft/test1.perft";

        auto parser = PerftParser();
        auto perft = parser.parse_perft(str_perft);
        auto fen = perft.fen_get();
        int depth = perft.depth_get();

        EXPECT_EQ(depth, 1);

        auto pair_1 = std::make_pair<board::PieceType, board::Color>
                    (board::PieceType::BISHOP, board::Color::WHITE);
        EXPECT_EQ(fen[board::Position(board::File::A, board::Rank::EIGHT)],
                    pair_1);
        auto pair_2 = std::make_pair<board::PieceType, board::Color>
                    (board::PieceType::QUEEN, board::Color::BLACK);
        EXPECT_EQ(fen[board::Position(board::File::B, board::Rank::EIGHT)],
                    pair_2);
        EXPECT_EQ(fen[board::Position(board::File::A, board::Rank::SEVEN)],
                    std::nullopt);
        EXPECT_EQ(fen[board::Position(board::File::B, board::Rank::SEVEN)],
                    std::nullopt);

        EXPECT_EQ(fen.side_to_move_get(), board::Color::WHITE);

        EXPECT_EQ(fen.castling_get()[0], 'K');

        EXPECT_EQ(fen.en_passant_target_get(), std::nullopt);
    }

    TEST(perft_parser, perft_short_line_en_passant) {

        std::string str_perft = "../tests/custom_perft/test2.perft";

        auto parser = PerftParser();
        auto perft = parser.parse_perft(str_perft);
        auto fen = perft.fen_get();
        int depth = perft.depth_get();

        EXPECT_EQ(depth, 1);

        auto pair_1 = std::make_pair<board::PieceType, board::Color>
                    (board::PieceType::PAWN, board::Color::WHITE);
        EXPECT_EQ(fen[board::Position(board::File::A, board::Rank::EIGHT)],
                    pair_1);
        auto pair_2 = std::make_pair<board::PieceType, board::Color>
                    (board::PieceType::KNIGHT, board::Color::BLACK);
        EXPECT_EQ(fen[board::Position(board::File::B, board::Rank::EIGHT)],
                    pair_2);
        EXPECT_EQ(fen[board::Position(board::File::A, board::Rank::SEVEN)],
                    pair_1);
        EXPECT_EQ(fen[board::Position(board::File::B, board::Rank::SEVEN)],
                    pair_2);

        EXPECT_EQ(fen.side_to_move_get(), board::Color::WHITE);

        EXPECT_EQ(fen.castling_get()[0], 'K');

        EXPECT_EQ(fen.en_passant_target_get(),
                    board::Position(board::File::A, board::Rank::THREE));
    }
}
