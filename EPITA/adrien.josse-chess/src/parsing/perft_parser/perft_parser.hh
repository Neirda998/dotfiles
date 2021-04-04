#pragma once

#include "fen_object.hh"
#include "fen_rank.hh"
#include "perft_object.hh"

namespace parsing {
    class PerftParser {
    public:
        PerftParser() {}

        FenRank parse_rank(std::string rank);
        FenObject parse_fen(std::vector<std::string> splited_input);
        PerftObject parse_perft(std::string filename);
    };
}
