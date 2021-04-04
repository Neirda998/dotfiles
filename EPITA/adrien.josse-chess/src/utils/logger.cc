#include "logger.hh"

namespace utils
{
    // C++ is a nice language.

    const std::string Logger::color_default = "\033[00m";
    const std::string Logger::color_red = "\033[31m";
    const std::string Logger::color_green = "\033[32m";
    const std::string Logger::color_yellow = "\033[33m";
    const std::string Logger::color_blue = "\033[34m";
    const std::string Logger::color_magenta = "\033[35m";
    const std::string Logger::color_cyan = "\033[36m";
    const std::string Logger::color_lightgray = "\033[37m";

#ifdef DEBUG
    const bool Logger::no_log = false;
#else
    const bool Logger::no_log = true;
#endif
}
