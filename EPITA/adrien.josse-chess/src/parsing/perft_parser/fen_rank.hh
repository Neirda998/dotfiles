#pragma once

#include <optional>
#include <utility>
#include <vector>

#include "color.hh"
#include "piece-type.hh"
#include "position.hh"

namespace parsing {
    class FenRank {
    public:
        using side_piece_t = std::pair<board::PieceType, board::Color>;
        using opt_piece_t = std::optional<side_piece_t>;

        FenRank(std::vector<opt_piece_t> pieces)
            : pieces_(pieces)
        {}

        opt_piece_t operator[](board::File file);

    private:
        std::vector<opt_piece_t> pieces_;

        size_t file_to_index(board::File file);
    };
}
