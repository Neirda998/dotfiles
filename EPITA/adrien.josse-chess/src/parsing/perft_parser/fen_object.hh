#pragma once

#include "fen_rank.hh"

namespace parsing {
    class FenObject {
    public:
        using side_piece_t = std::pair<board::PieceType, board::Color>;
        using opt_piece_t = std::optional<side_piece_t>;

        FenObject(std::vector<FenRank> ranks, board::Color side_to_move,
                    std::vector<char> castling,
                    std::optional<board::Position> en_passant_target)
            : ranks_(ranks)
            , side_to_move_(side_to_move)
            , castling_(castling)
            , en_passant_target_(en_passant_target)
        {}

        opt_piece_t operator[](const board::Position& pos);
        board::Color side_to_move_get() const;
        std::vector<char> castling_get() const;
        std::optional<board::Position> en_passant_target_get() const;
        std::vector<FenRank> ranks_get() const;

    private:
        std::vector<FenRank> ranks_;
        board::Color side_to_move_;
        std::vector<char> castling_;
        std::optional<board::Position> en_passant_target_;

        size_t rank_to_index(board::Rank rank) const;
    };
}
