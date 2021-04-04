#pragma once

#include <optional>
#include <tuple>
#include <utility>
#include <vector>

#include "color.hh"
#include "fen_rank.hh"
#include "move.hh"
#include "piece-type.hh"
#include "position.hh"

namespace board
{
    class ChessboardRepresentation
    {
    public:
        // Default board constructor, sets the board up in starting position.
        ChessboardRepresentation();

        ChessboardRepresentation
        (const ChessboardRepresentation& representation) = default;

        // Builds the bitboards from a vector of coordinates.
        // pieces:
        // 0 --> file
        // 1 --> rank
        // 2 --> piece_type
        ChessboardRepresentation
        (std::vector<std::tuple<size_t, size_t, size_t>> pieces);

        inline std::vector<uint64_t> bitboards_get() const
        {
            return bitboards_;
        }

        constexpr size_t get_sqr_piece(size_t file, size_t rank) const
        {
            for (size_t bit_idx = 0; bit_idx < 12; ++bit_idx)
            {
                if (bitboards_[bit_idx] & pos_to_int(file, rank))
                    return bit_idx;
            }
            return 12;
        }

        // Splits the bitboard into sub_boards containing a single piece.
        // Size of the return vector corresponds to the number of pieces.
        std::vector<uint64_t> split_boards(int bit_idx) const;

        void do_move(const Move& move, bool white, uint64_t en_passant);

        // Generates ASCII representations of the bitboards
        // with spaces and newlines.
        // If no piece is given, it displays the combination
        // of all the bitboards.
        std::string generate_ascii_board(size_t bit_idx) const;

        bool operator==(const ChessboardRepresentation& rep) const;

    private:

        // Pieces order in bitboards is as follows:
        // (WHITE): Q, R, B, N, P, K
        // (BLACK): Q, R, B, N, P, K
        std::vector<uint64_t> bitboards_;
    };

    class BitboardHash {
    public:

        // Use linear xor operations on bitboard vector
        // as hash function.
        uint64_t operator()(const ChessboardRepresentation& rep) const
        {
            uint64_t hash = 0;
            uint64_t hash_neg = 0;

            for (auto bitboard : rep.bitboards_get())
            {
                hash ^= bitboard;
                hash_neg ^= ~bitboard;
            }

            return hash ^ hash_neg;
        }
    };
}
