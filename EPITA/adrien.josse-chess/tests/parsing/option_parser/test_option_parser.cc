#include <gtest/gtest.h>
#include <vector>

#include "option_parser.hh"

namespace parsing {

    TEST(option_parser, no_options) {

        std::string str = "./420chessh";

        std::vector<char*> argv;
        argv.push_back((char*)str.data());
        argv.push_back(nullptr);

        auto option_parser = parse_options(argv.size() - 1, argv.data());

        EXPECT_EQ(option_parser.get_error_parse(), false);
        EXPECT_EQ(option_parser.get_help(), false);
        EXPECT_EQ(option_parser.get_pgn_path(), "");
        EXPECT_EQ(option_parser.get_listener_paths().size(), 0);
        EXPECT_EQ(option_parser.get_perft_path(), "");
    }

    TEST(option_parser, help) {
        std::string arg1 = "./420chessh";
        std::string arg2 = "-h";

        std::vector<char*> argv;
        argv.push_back((char*)arg1.data());
        argv.push_back((char*)arg2.data());
        argv.push_back(nullptr);

        auto option_parser = parse_options(argv.size() - 1, argv.data());

        EXPECT_EQ(option_parser.get_error_parse(), false);
        EXPECT_EQ(option_parser.get_help(), true);
        EXPECT_EQ(option_parser.get_pgn_path(), "");
        EXPECT_EQ(option_parser.get_listener_paths().size(), 0);
        EXPECT_EQ(option_parser.get_perft_path(), "");
    }

    TEST(option_parser, pgn_file) {
        std::string arg1 = "./420chessh";
        std::string arg2 = "--pgn";
        std::string arg3 = "game";

        std::vector<char*> argv;
        argv.push_back((char*)arg1.data());
        argv.push_back((char*)arg2.data());
        argv.push_back((char*)arg3.data());
        argv.push_back(nullptr);

        auto option_parser = parse_options(argv.size() - 1, argv.data());

        EXPECT_EQ(option_parser.get_error_parse(), false);
        EXPECT_EQ(option_parser.get_help(), false);
        EXPECT_EQ(option_parser.get_pgn_path(), "game");
        EXPECT_EQ(option_parser.get_listener_paths().size(), 0);
        EXPECT_EQ(option_parser.get_perft_path(), "");
    }

    TEST(option_parser, perft_file) {
        std::string arg1 = "./420chessh";
        std::string arg2 = "--perft";
        std::string arg3 = "chess";

        std::vector<char*> argv;
        argv.push_back((char*)arg1.data());
        argv.push_back((char*)arg2.data());
        argv.push_back((char*)arg3.data());
        argv.push_back(nullptr);

        auto option_parser = parse_options(argv.size() - 1, argv.data());

        EXPECT_EQ(option_parser.get_error_parse(), false);
        EXPECT_EQ(option_parser.get_help(), false);
        EXPECT_EQ(option_parser.get_pgn_path(), "");
        EXPECT_EQ(option_parser.get_listener_paths().size(), 0);
        EXPECT_EQ(option_parser.get_perft_path(), "chess");
    }

    TEST(option_parser, listeners) {
        std::string arg1 = "./420chessh";
        std::string arg2 = "--listeners";
        std::string arg3 = "foo";
        std::string arg4 = "bar";
        std::string arg5 = "420sh";

        std::vector<char*> argv;
        argv.push_back((char*)arg1.data());
        argv.push_back((char*)arg2.data());
        argv.push_back((char*)arg3.data());
        argv.push_back((char*)arg4.data());
        argv.push_back((char*)arg5.data());
        argv.push_back(nullptr);

        auto option_parser = parse_options(argv.size() - 1, argv.data());

        EXPECT_EQ(option_parser.get_error_parse(), false);
        EXPECT_EQ(option_parser.get_help(), false);
        EXPECT_EQ(option_parser.get_pgn_path(), "");
        EXPECT_EQ(option_parser.get_listener_paths().size(), 3);
        EXPECT_STREQ(option_parser.get_listener_paths().at(0).data(), "foo");
        EXPECT_STREQ(option_parser.get_listener_paths().at(1).data(), "bar");
        EXPECT_STREQ(option_parser.get_listener_paths().at(2).data(), "420sh");
        EXPECT_EQ(option_parser.get_perft_path(), "");
    }

    TEST(option_parser, wrong) {
        std::string arg1 = "./420chessh";
        std::string arg2 = "--couille";

        std::vector<char*> argv;
        argv.push_back((char*)arg1.data());
        argv.push_back((char*)arg2.data());
        argv.push_back(nullptr);

        auto option_parser = parse_options(argv.size() - 1, argv.data());

        EXPECT_EQ(option_parser.get_error_parse(), true);
        EXPECT_EQ(option_parser.get_help(), false);
        EXPECT_EQ(option_parser.get_pgn_path(), "");
        EXPECT_EQ(option_parser.get_listener_paths().size(), 0);
        EXPECT_EQ(option_parser.get_perft_path(), "");
    }
}
