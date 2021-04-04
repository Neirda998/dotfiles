#include <gtest/gtest.h>

#include "fen_rank.hh"

namespace parsing {

    TEST(fen_rank, empty_rank) {
        using side_piece_t = std::pair<board::PieceType, board::Color>;
        using opt_piece_t = std::optional<side_piece_t>;

        std::vector<opt_piece_t> pieces;
        for (int i = 0; i < 8; ++i)
            pieces.push_back(std::nullopt);

        auto rank = FenRank(pieces);

        EXPECT_EQ(rank[board::File::A], std::nullopt);
        EXPECT_EQ(rank[board::File::B], std::nullopt);
        EXPECT_EQ(rank[board::File::C], std::nullopt);
        EXPECT_EQ(rank[board::File::D], std::nullopt);
        EXPECT_EQ(rank[board::File::E], std::nullopt);
        EXPECT_EQ(rank[board::File::F], std::nullopt);
        EXPECT_EQ(rank[board::File::G], std::nullopt);
        EXPECT_EQ(rank[board::File::H], std::nullopt);
    }

    TEST(fen_rank, some_pieces) {
        using side_piece_t = std::pair<board::PieceType, board::Color>;
        using opt_piece_t = std::optional<side_piece_t>;

        std::vector<opt_piece_t> pieces;
        pieces.push_back(std::nullopt);
        pieces.push_back(std::make_pair<board::PieceType, board::Color>
                                 (board::PieceType::ROOK, board::Color::WHITE));
        pieces.push_back(std::make_pair<board::PieceType, board::Color>
                                 (board::PieceType::KNIGHT, board::Color::BLACK));
        pieces.push_back(std::make_pair<board::PieceType, board::Color>
                                 (board::PieceType::BISHOP, board::Color::WHITE));
        pieces.push_back(std::make_pair<board::PieceType, board::Color>
                                 (board::PieceType::QUEEN, board::Color::BLACK));
        pieces.push_back(std::make_pair<board::PieceType, board::Color>
                                 (board::PieceType::KING, board::Color::WHITE));
        pieces.push_back(std::make_pair<board::PieceType, board::Color>
                                 (board::PieceType::PAWN, board::Color::BLACK));
        pieces.push_back(std::nullopt);

        auto rank = FenRank(pieces);

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
}
