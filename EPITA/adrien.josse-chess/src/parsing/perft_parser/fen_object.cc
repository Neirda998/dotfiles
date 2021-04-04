#include "fen_object.hh"

namespace parsing {

    std::optional<std::pair<board::PieceType, board::Color>>
    FenObject::operator[](const board::Position& pos) {
        return ranks_.at(rank_to_index(pos.rank_get()))[pos.file_get()];
    }

    size_t FenObject::rank_to_index(board::Rank rank) const {
        switch (rank) {

        case board::Rank::ONE:
            return 7;
        case board::Rank::TWO:
            return 6;
        case board::Rank::THREE:
            return 5;
        case board::Rank::FOUR:
            return 4;
        case board::Rank::FIVE:
            return 3;
        case board::Rank::SIX:
            return 2;
        case board::Rank::SEVEN:
            return 1;
        case board::Rank::EIGHT:
            return 0;
        }
        return 8;
    }

    /* Getters */

    board::Color FenObject::side_to_move_get() const {
        return this->side_to_move_;
    }

    std::vector<char> FenObject::castling_get() const {
        return this->castling_;
    }

    std::optional<board::Position> FenObject::en_passant_target_get() const {
        return this->en_passant_target_;
    }

    std::vector<FenRank> FenObject::ranks_get() const {
        return this->ranks_;
    }
}
