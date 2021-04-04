#pragma once

#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>

#include <iostream>

namespace parsing {
    class OptionParser {
    public:

        OptionParser(bool help,
                     std::string pgn_path,
                     std::vector<std::string> listener_paths,
                     std::string perft_path,
                     bool error_parse)
            : help_(help)
            , pgn_path_(pgn_path)
            , listener_paths_(listener_paths)
            , perft_path_(perft_path)
            , error_parse_(error_parse)
        {}

        bool get_help();
        std::string get_pgn_path();
        std::vector<std::string> get_listener_paths();
        std::string get_perft_path();
        bool get_error_parse();

    private:
        bool help_;
        std::string pgn_path_;
        std::vector<std::string> listener_paths_;
        std::string perft_path_;
        bool error_parse_;
    };

    OptionParser parse_options(int argc, char **argv);
}
