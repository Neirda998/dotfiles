#pragma once

#include <optional>
#include <utility>

#include "chessboard-representation.hh"
#include "color.hh"
#include "piece-type.hh"
#include "position.hh"
#include "utils.hh"

#include <iostream>

namespace board {
    class Move
    {
    public:
        using side_piece_t = std::pair<PieceType, Color>;
        using opt_piece_t = std::optional<side_piece_t>;

        Move() = default;

        Move(uint64_t src_state, uint64_t dst_state,
            PieceType piece, std::optional<PieceType> promotion,
            std::optional<PieceType> capture,
            bool double_pawn_push, bool king_castling,
            bool queen_castling, bool en_passant)
            : src_state_(src_state)
            , dst_state_(dst_state)
            , piece_(piece)
            , promotion_(promotion)
            , capture_(capture)
            , double_pawn_push_(double_pawn_push)
            , king_castling_(king_castling)
            , queen_castling_(queen_castling)
            , en_passant_(en_passant)
            {}

        bool operator==(const Move& rhs) const
        {
            return src_state_ == rhs.src_state_get()
                    && dst_state_ == rhs.dst_state_get()
                    && piece_ == rhs.piece_get()
                    && promotion_ == rhs.promotion_get()
                    && capture_ == rhs.capture_get()
                    && double_pawn_push_ == rhs.double_pawn_push_get()
                    && king_castling_ == rhs.king_castling_get()
                    && queen_castling_ == rhs.queen_castling_get()
                    && en_passant_ == rhs.en_passant_get();
        }

        Position src_position_get() const
        {
            int log = 0;
            uint64_t board = src_state_get();
            while (board > 1) {
                board /= 2;
                log++;
            }

            File file = static_cast<File>(log / 8);
            Rank rank = static_cast<Rank>(log % 8);

            return Position(file, rank);
        }

        Position dst_position_get() const
        {
            int log = 0;
            uint64_t board = dst_state_get();
            while (board > 1) {
                board /= 2;
                log++;
            }

            File file = static_cast<File>(log / 8);
            Rank rank = static_cast<Rank>(log % 8);

            return Position(file, rank);
        }

        inline PieceType piece_get() const
        {
            return piece_;
        }

        inline uint64_t src_state_get() const
        {
            return src_state_;
        }

        inline uint64_t dst_state_get() const
        {
            return dst_state_;
        }

        inline std::optional<PieceType> promotion_get() const
        {
            return promotion_;
        }

        inline std::optional<PieceType> capture_get() const
        {
            return capture_;
        }

        inline bool double_pawn_push_get() const
        {
            return double_pawn_push_;
        }

        inline bool king_castling_get() const
        {
            return king_castling_;
        }

        inline bool queen_castling_get() const
        {
            return queen_castling_;
        }

        inline bool en_passant_get() const
        {
            return en_passant_;
        }

        inline void print() const
        {
            auto src_coord = get_coordinates(src_state_);
            auto dst_coord = get_coordinates(dst_state_);
            std::vector<char> pieces = { 'q', 'r', 'b', 'n', 'p', 'k'};

            char promo = promotion_ != std::nullopt ?
                    pieces[static_cast<size_t>(promotion_.value())] : 'X';
            char captur = capture_ != std::nullopt ?
                    pieces[static_cast<size_t>(capture_.value())] : 'X';

            std::cout
                << "source: " << src_coord.first << ' ' << src_coord.second
                << " dest: " << dst_coord.first << ' ' << dst_coord.second
                << " piece: " << pieces[static_cast<size_t>(piece_)]
                << "\npromotion: " << promo
                << " capture: " << captur << std::endl
                << "double_pawn_push: " << double_pawn_push_
                << " king_castling: " << king_castling_
                << " queen_castling: " << queen_castling_
                << " en_passant: " << en_passant_ << std::endl;
        }

    private:

        uint64_t src_state_;

        uint64_t dst_state_;

        PieceType piece_;

        std::optional<PieceType> promotion_;

        std::optional<PieceType> capture_;

        bool double_pawn_push_;

        bool king_castling_;

        bool queen_castling_;

        bool en_passant_;
    };
}
