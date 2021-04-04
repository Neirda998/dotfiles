#include "perft_object.hh"

namespace parsing {

    FenObject PerftObject::fen_get() {
        return this->fen_;
    }

    int PerftObject::depth_get() {
        return this->depth_;
    }
}
