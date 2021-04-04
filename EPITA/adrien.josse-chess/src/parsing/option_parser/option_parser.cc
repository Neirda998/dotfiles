#include "option_parser.hh"

namespace parsing {

    bool OptionParser::get_help() {
        return this->help_;
    }

    std::string OptionParser::get_pgn_path() {
        return this->pgn_path_;
    }

    std::vector<std::string> OptionParser::get_listener_paths() {
        return this->listener_paths_;
    }

    std::string OptionParser::get_perft_path() {
        return this->perft_path_;
    }

    bool OptionParser::get_error_parse() {
        return this->error_parse_;
    }

    OptionParser parse_options(int argc, char **argv) {

        namespace po = boost::program_options;
        po::options_description desc("Allowed options:");

        std::vector<std::string> listener_paths;
        desc.add_options()
            ("help,h", "show usage")
            ("pgn", po::value<std::string>(), "path to the PGN game file")
            ("listeners,l",
                po::value<std::vector<std::string>>
                (&listener_paths)->multitoken(),
                "list of paths to listener plugins")
            ("perft", po::value<std::string>(), "path to a perft file");

        po::variables_map vm;
        try {
            po::store(po::parse_command_line(argc, argv, desc), vm);
            po::notify(vm);
        } catch (std::exception& e) {
            std::cerr << "Invalid option" << std::endl;
            std::cerr << desc << std::endl;
            std::vector<std::string> empty;
            return OptionParser(false, "", empty, "", true);
        }

        bool help = vm.count("help") > 0;
        std::string pgn_path = "";
        if (vm.count("pgn") > 0)
            pgn_path = vm["pgn"].as<std::string>();

        std::vector<std::string> listeners;
        if (vm.count("listeners") > 0)
            listeners = vm["listeners"].as<std::vector<std::string>>();

        std::string perft_path = "";
        if (vm.count("perft") > 0)
            perft_path = vm["perft"].as<std::string>();

        if (help)
            std::cout << desc << std::endl;

        return OptionParser(help, pgn_path, listeners, perft_path, false);
    }
}
