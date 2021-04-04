#pragma once

#include "fen_object.hh"

namespace parsing {
    class PerftObject {
    public:
        PerftObject(FenObject fen, int depth)
            : fen_(fen)
            , depth_(depth)
        {}

        FenObject fen_get();
        int depth_get();

    private:
        FenObject fen_;
        int depth_;
    };
}
