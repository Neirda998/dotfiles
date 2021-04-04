#include <gtest/gtest.h>

#include "fen_object.hh"

namespace parsing {

    TEST(fen_object, empty_board_1x1) {
        using side_piece_t = std::pair<board::PieceType, board::Color>;
        using opt_piece_t = std::optional<side_piece_t>;

        std::vector<opt_piece_t> pieces;
        std::vector<FenRank> ranks;
        std::vector<char> empty;

        pieces.push_back(std::nullopt);
        ranks.push_back(FenRank(pieces));
        auto fen_obj = FenObject(ranks, board::Color::WHITE, empty, std::nullopt);

        // 8 matches the top line, so A8 --> first case of the board
        auto pos = board::Position(board::File::A, board::Rank::EIGHT);
        EXPECT_EQ(fen_obj[pos], std::nullopt);
    }

    TEST(fen_object, filled_board_1x1) {
        using side_piece_t = std::pair<board::PieceType, board::Color>;
        using opt_piece_t = std::optional<side_piece_t>;

        std::vector<opt_piece_t> pieces;
        std::vector<FenRank> ranks;
        std::vector<char> empty;

        pieces.push_back(std::make_pair<board::PieceType, board::Color>
                                (board::PieceType::BISHOP, board::Color::WHITE));
        ranks.push_back(FenRank(pieces));
        auto fen_obj = FenObject(ranks, board::Color::BLACK, empty, std::nullopt);

        // 8 matches the top line, so A8 --> first case of the board
        auto pos = board::Position(board::File::A, board::Rank::EIGHT);
        auto pair = std::make_pair<board::PieceType, board::Color>
                            (board::PieceType::BISHOP, board::Color::WHITE);
        EXPECT_EQ(fen_obj[pos], pair);
    }
}
