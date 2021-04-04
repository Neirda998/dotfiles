#include "fen_rank.hh"

namespace parsing {

    std::optional<std::pair<board::PieceType, board::Color>>
    FenRank::operator[](board::File file) {
        return this->pieces_.at(file_to_index(file));
    }

    size_t FenRank::file_to_index(board::File file) {
        switch (file) {
        case board::File::A:
            return 0;
        case board::File::B:
            return 1;
        case board::File::C:
            return 2;
        case board::File::D:
            return 3;
        case board::File::E:
            return 4;
        case board::File::F:
            return 5;
        case board::File::G:
            return 6;
        case board::File::H:
            return 7;
        }
        return 8;
    }
}
