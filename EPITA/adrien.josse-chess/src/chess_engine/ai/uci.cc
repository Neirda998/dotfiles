#include "logger.hh"
#include "perft_parser.hh"
#include "uci.hh"
#include "utils.hh"

#include <fnmatch.h>
#include <iostream>

namespace ai
{
    namespace
    {
        std::string get_input(const std::string& expected = "*")
        {
            // Get a command following the expected globbing
            // Ignoring all unrecognized commands
            std::string buffer;
            std::string position;
            do
            {
                std::getline(std::cin, buffer);
                utils::Logger::uci_input(buffer);

                if ("quit" == buffer || "stopuci" == buffer)
                    exit(0);

                if ("isready" == buffer)
                {
                    std::cout << "readyok" << std::endl;
                    utils::Logger::uci_output("readyok");
                }

                if (!fnmatch("position *", buffer.c_str(), 0))
                    position = buffer;

                if (!fnmatch("go *", buffer.c_str(), 0))
                    break;

            } while (fnmatch(expected.c_str(), buffer.c_str(), 0));
            return position;
        }
    } // namespace

    void init(const std::string& name)
    {
        get_input("uci");

        std::cout << "id name " << name << '\n';
        utils::Logger::uci_output(std::string("id name ").append(name));

        std::cout << "id author " << name << '\n';
        utils::Logger::uci_output(std::string("id author ").append(name));

        std::cout << "uciok" << std::endl;
        utils::Logger::uci_output("uciok ");

        get_input("isready");
    }

    void play_move(const std::string& move)
    {
        // Send the computed move
        std::cout << "bestmove " << move << std::endl;
        utils::Logger::uci_output(std::string("bestmove ").append(move));
    }

    std::string get_board()
    {
        return get_input("420chessh");
    }

    static const std::map<std::string, board::PieceType> uci_promotion =
    {
        {"q", board::PieceType::QUEEN},
        {"r", board::PieceType::ROOK},
        {"b", board::PieceType::BISHOP},
        {"n", board::PieceType::KNIGHT}
    };

    void setup(board::Chessboard& board)
    {
        auto uci_str = get_board();

        std::string moves;

        size_t move_pos = uci_str.find("moves");

        std::string last = board.uci_last_get();

        board.uci_last_set(uci_str);

        if (last != "" && uci_str.compare(0, last.size(), uci_str) == 0)
        {
            uci_str = std::string("moves").append(
                    uci_str.substr(last.size()));
            move_pos = 0;
        }
        else if (uci_str.find("startpos") == std::string::npos)
        {
            std::string position = uci_str.substr(13, move_pos - 14);

            auto parser = parsing::PerftParser();

            auto split_input = board::split_string(position, ' ');
            auto fen_object = parser.parse_fen(split_input);

            board = board::Chessboard(fen_object);
        }
        else
        {
            board = board::Chessboard();
        }

        if (move_pos != std::string::npos)
        {
            moves = uci_str.substr(move_pos + 6,
                                   uci_str.size() - move_pos - 5);

            for (auto move_str : board::split_string(moves, ' '))
            {
                auto promotion = move_str.substr(4);

                auto move = board.create_move(
                    board::str_to_pos(false, move_str.substr(0, 2)),
                    board::str_to_pos(false, move_str.substr(2, 2)),
                    promotion == "" ? std::nullopt :
                    std::optional<board::PieceType>(
                        uci_promotion.at(promotion))
                );

                board.do_move(move, true);
            }
        }
    }
} // namespace ai
