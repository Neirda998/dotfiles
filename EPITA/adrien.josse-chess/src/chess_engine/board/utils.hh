#pragma once

#include <cstdint>
#include <string>
#include <optional>
#include <vector>

#include "color.hh"
#include "piece-type.hh"
#include "position.hh"

namespace board
{
    using side_piece_t = std::pair<PieceType, Color>;
    using opt_piece_t = std::optional<side_piece_t>;

    constexpr std::size_t side_piece_to_bit_idx(side_piece_t layer)
    {
        return static_cast<std::size_t>(layer.first)
            + static_cast<std::size_t>(layer.second) * 6;
    }

    constexpr std::uint64_t pos_to_int(std::size_t file, std::size_t rank)
    {
        std::size_t sqr_idx = 8 * file + rank;
        std::uint64_t tmp = 1;
        return tmp << (sqr_idx);
    }

    constexpr bool is_power_of_two(std::uint64_t n)
    {
        return n != 0 && (n & (n-1)) == 0;
    }

    constexpr std::pair<int, int> get_coordinates(std::uint64_t board)
    {
        if (!is_power_of_two(board))
            return std::make_pair<int, int>(-1, -1);

        int log = 0;
        while (board > 1)
        {
            board /= 2;
            log++;
        }

        return std::make_pair<int, int>(log / 8, log % 8);
    }

    inline board::Position str_to_pos(bool uppercase, std::string str)
    {
        auto letter = uppercase ? 'A' : 'a';
        return board::Position(static_cast<board::File>(str[0] - letter),
                               static_cast<board::Rank>(str[1] - '1'));
    }

    std::string pos_to_str(bool uppercase, const board::Position& pos);

    std::vector<std::string> split_string(std::string str,
            const char delim);
}
