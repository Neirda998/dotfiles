#include <fstream>
#include <iostream>

#include "perft_parser.hh"
#include "utils.hh"

namespace parsing {

    static std::pair<board::PieceType, board::Color> parse_piece(char c) {
        bool is_black = c >= 'b' && c <= 'r';
        char p = is_black ? c - 'a' + 'A' : c;

        switch (p) {
        case 'B':
            return std::make_pair<board::PieceType, board::Color>
                    (board::PieceType::BISHOP,
                    is_black ? board::Color::BLACK : board::Color::WHITE);
        case 'K':
            return std::make_pair<board::PieceType, board::Color>
                    (board::PieceType::KING,
                    is_black ? board::Color::BLACK : board::Color::WHITE);
        case 'N':
            return std::make_pair<board::PieceType, board::Color>
                    (board::PieceType::KNIGHT,
                    is_black ? board::Color::BLACK : board::Color::WHITE);
        case 'P':
            return std::make_pair<board::PieceType, board::Color>
                    (board::PieceType::PAWN,
                    is_black ? board::Color::BLACK : board::Color::WHITE);
        case 'Q':
            return std::make_pair<board::PieceType, board::Color>
                    (board::PieceType::QUEEN,
                    is_black ? board::Color::BLACK : board::Color::WHITE);
        default: // case 'R'
            return std::make_pair<board::PieceType, board::Color>
                    (board::PieceType::ROOK,
                    is_black ? board::Color::BLACK : board::Color::WHITE);
        }
    }

    FenRank PerftParser::parse_rank(std::string rank) {
        using side_piece_t = std::pair<board::PieceType, board::Color>;
        using opt_piece_t = std::optional<side_piece_t>;

        std::vector<opt_piece_t> pieces;
        size_t ln = rank.size();
        for (size_t i = 0; i < ln; i++) {
            if (rank[i] >= '1' && rank[i] <= '8') {
                size_t k = rank[i] - '0';
                for (size_t j = 0; j < k; j++)
                    pieces.push_back(std::nullopt);
            }
            else
                pieces.push_back(parse_piece(rank[i]));
        }
        return FenRank(pieces);
    }

    static std::optional<board::Position>
    parse_en_passant_target(std::string str) {
        if (str.compare("-") == 0)
            return std::nullopt;

        char file = str[0];
        char rank = str[1];
        bool is_top = rank == '6';

        switch (file) {
        case 'a':
            return board::Position(board::File::A,
            is_top ? board::Rank::SIX : board::Rank::THREE);
        case 'b':
            return board::Position(board::File::B,
            is_top ? board::Rank::SIX : board::Rank::THREE);
        case 'c':
            return board::Position(board::File::C,
            is_top ? board::Rank::SIX : board::Rank::THREE);
        case 'd':
            return board::Position(board::File::D,
            is_top ? board::Rank::SIX : board::Rank::THREE);
        case 'e':
            return board::Position(board::File::E,
            is_top ? board::Rank::SIX : board::Rank::THREE);
        case 'f':
            return board::Position(board::File::F,
            is_top ? board::Rank::SIX : board::Rank::THREE);
        case 'g':
            return board::Position(board::File::G,
            is_top ? board::Rank::SIX : board::Rank::THREE);
        default: // case 'h'
            return board::Position(board::File::H,
            is_top ? board::Rank::SIX : board::Rank::THREE);
        }
    }

    FenObject PerftParser::parse_fen(std::vector<std::string> splited_input) {
        std::vector<FenRank> ranks;

        auto ranks_strings = board::split_string(splited_input[0], '/');
        for (size_t i = 0; i < ranks_strings.size(); i++)
            ranks.push_back(parse_rank(ranks_strings[i]));

        bool black = splited_input[1].compare("b") == 0;

        std::vector<char> castling;
        for (size_t i = 0; i < splited_input[2].size(); i++)
            castling.push_back(splited_input[2][i]);

        return FenObject(ranks, black ?
                         board::Color::BLACK : board::Color::WHITE,
                         castling, parse_en_passant_target(splited_input[3]));
    }

    PerftObject PerftParser::parse_perft(std::string filename) {
        auto in_str = std::ifstream(filename);
        auto line = std::string();
        if (in_str.is_open())
        {
            std::getline(in_str, line);
            in_str.close();
        }

        auto splited_input = board::split_string(line, ' ');
        int depth = std::stoi(splited_input[splited_input.size() - 1]);
        return PerftObject(parse_fen(splited_input), depth);
    }
}
