#pragma once

#include <iostream>

namespace utils
{
    class Logger
    {
    public:
        inline static void log(const std::string& msg)
        {
            std::cerr << color_lightgray << msg << color_default << std::endl;
        }

        inline static void uci_input(const std::string& msg)
        {
            if (no_log)
                return;
            std::string color = color_yellow;
            std::cerr << color << "["
                      << color_default << "UCI"
                      << color << "]" << "["
                      << color_default << "<<"
                      << color << "]:$> "
                      << msg << color_default << std::endl;
        }

        inline static void uci_output(const std::string& msg)
        {
            if (no_log)
                return;
            std::string color = color_green;
            std::cerr << color << "["
                      << color_default << "UCI"
                      << color << "]" << "["
                      << color_default << ">>"
                      << color << "]:$> "
                      << msg << color_default << std::endl;
        }

        inline static void chessboard(const std::string& board)
        {
            if (no_log)
                return;
            std::string color = color_blue;
            std::cerr << color << "=====["
                      << color_default << "BOARD"
                      << color << "]=====" << color_default
                      << std::endl << board
                      << color << "================="
                      << color_default << std::endl;
        }

        inline static void starteval()
        {
            if (no_log)
                return;
            std::string color = color_cyan;
            std::cerr << color << "=====["
                      << color_default << "EVALS"
                      << color << "]====="
                      << color_default << std::endl;
        }

        inline static void eval(int eval)
        {
            if (no_log)
                return;
            std::string color = color_cyan;
            std::cerr << color
                      << color_default << eval
                      << color << ", "
                      << color_default;
        }


        inline static void endeval(int best_eval)
        {
            if (no_log)
                return;
            std::string color = color_cyan;
            std::cerr << color << "["
                      << color_default << "BESTEVAL"
                      << color << "]:$> "
                      << best_eval << std::endl
                      << "================="
                      << color_default << std::endl;
        }

        inline static void repetitions(bool is_real_move, int nb)
        {
            if (no_log || !is_real_move)
                return;
            std::string color = color_cyan;
            std::cerr << color << "["
                      << color_default << "HISTORY"
                      << color << "]:$> There were "
                      << nb << " repetitions!"
                      << color_default << std::endl;
        }

        inline static void listener(const std::string& msg)
        {
            std::string color = color_magenta;
            std::cerr << color << "====["
                      << color_default << "LISTENER"
                      << color << "]====" << color_default
                      << std::endl << msg
                      << color << "============="
                      << color_default << std::endl;
        }

    private:
        static const std::string color_default;
        static const std::string color_red;
        static const std::string color_green;
        static const std::string color_yellow;
        static const std::string color_blue;
        static const std::string color_magenta;
        static const std::string color_cyan;
        static const std::string color_lightgray;

        static const bool no_log;
    };
}
