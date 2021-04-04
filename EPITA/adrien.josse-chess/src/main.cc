#include <iostream>
#include <vector>

#include "chessboard.hh"
#include "option_parser.hh"
#include "perft_engine.hh"
#include "perft_parser.hh"
#include "pgn-move.hh"
#include "pgn-parser.hh"
#include "listener_manager.hh"
#include "piece-type.hh"
#include "position.hh"


int main(int argc, char** argv)
{
    parsing::OptionParser options = parsing::parse_options(argc, argv);

    if (options.get_error_parse())
        return 1;
    if (options.get_help())
        return 0;

    auto perft_path = options.get_perft_path();
    board::Chessboard board;
    if (perft_path != "")
    {
        auto perft_parser = parsing::PerftParser();
        auto perft_obj = perft_parser.parse_perft(perft_path);
        board = board::Chessboard(perft_obj.fen_get());

        auto perft_engine = perft_engine::PerftEngine();

        std::cout << perft_engine.compute(board, perft_obj.depth_get())
                  << std::endl;

        return 0;
    }

    auto pgn_path = options.get_pgn_path();
    auto is_pgn = pgn_path != "";
    const std::vector<board::PgnMove> moves = is_pgn ?
        pgn_parser::parse_pgn(pgn_path)
        : std::vector<board::PgnMove>();
    auto manager = listener::ListenerManager(options.get_listener_paths(),
                                             board);

    manager.register_board(board);

    // Play loop taking mode: 0.human 1.ai 2.pgn
    manager.play(moves, is_pgn);

    manager.close_listeners();

    return 0;
}
