#include <gtest/gtest.h>

#include "chessboard.hh"

TEST(chessboard, empty_fen_object_constructor)
{
    using side_piece_t = std::pair<board::PieceType, board::Color>;
    using opt_piece_t = std::optional<side_piece_t>;

    std::vector<opt_piece_t> pieces;
    std::vector<parsing::FenRank> ranks;
    std::vector<char> empty;
    empty.push_back('-');

    for (size_t i = 0; i < 8; ++i)
        pieces.push_back(std::nullopt);
    for (size_t i = 0; i < 8; ++i)
        ranks.push_back(parsing::FenRank(pieces));
    auto fen_obj = parsing::FenObject(ranks, board::Color::WHITE,
                                      empty, std::nullopt);

    auto chessboard = board::Chessboard(fen_obj);
    std::string check = "8 . . . . . . . . \n"
                        "7 . . . . . . . . \n"
                        "6 . . . . . . . . \n"
                        "5 . . . . . . . . \n"
                        "4 . . . . . . . . \n"
                        "3 . . . . . . . . \n"
                        "2 . . . . . . . . \n"
                        "1 . . . . . . . . \n"
                        "  A B C D E F G H \n";


    EXPECT_TRUE(chessboard.white_turn_get());
    EXPECT_FALSE(chessboard.white_king_castling_get());
    EXPECT_FALSE(chessboard.white_queen_castling_get());
    EXPECT_FALSE(chessboard.black_king_castling_get());
    EXPECT_FALSE(chessboard.black_queen_castling_get());
    EXPECT_EQ(chessboard.rep_get().generate_ascii_board(12), check);
}

TEST(chessboard, fen_object_constructor_castling_full_pawn)
{
    using side_piece_t = std::pair<board::PieceType, board::Color>;
    using opt_piece_t = std::optional<side_piece_t>;

    std::vector<opt_piece_t> pieces;
    std::vector<parsing::FenRank> ranks;
    std::vector<char> castling_opts;
    castling_opts.push_back('K');
    castling_opts.push_back('q');

    auto pair = std::make_pair<board::PieceType, board::Color>
                              (board::PieceType::PAWN, board::Color::BLACK);
    for (size_t i = 0; i < 8; ++i)
        pieces.push_back(pair);
    for (size_t i = 0; i < 8; ++i)
        ranks.push_back(parsing::FenRank(pieces));
    auto fen_obj = parsing::FenObject(ranks, board::Color::BLACK,
                                      castling_opts, std::nullopt);

    auto chessboard = board::Chessboard(fen_obj);
    std::string check = "8 p p p p p p p p \n"
                        "7 p p p p p p p p \n"
                        "6 p p p p p p p p \n"
                        "5 p p p p p p p p \n"
                        "4 p p p p p p p p \n"
                        "3 p p p p p p p p \n"
                        "2 p p p p p p p p \n"
                        "1 p p p p p p p p \n"
                        "  A B C D E F G H \n";


    EXPECT_FALSE(chessboard.white_turn_get());
    EXPECT_TRUE(chessboard.white_king_castling_get());
    EXPECT_FALSE(chessboard.white_queen_castling_get());
    EXPECT_FALSE(chessboard.black_king_castling_get());
    EXPECT_TRUE(chessboard.black_queen_castling_get());
    EXPECT_EQ(chessboard.rep_get().generate_ascii_board(12), check);
}
