#include "utils.hh"

#include <sstream>

namespace board
{

    std::string pos_to_str(bool uppercase, const board::Position& pos)
    {
        std::stringstream str;
        auto letter = uppercase ? 'A' : 'a';
        str << static_cast<char>(letter + static_cast<int>(pos.file_get()))
            << static_cast<char>('1' + static_cast<int>(pos.rank_get()));
        return str.str();
    }

    std::vector<std::string> split_string(std::string str,
            const char delim)
    {
        std::vector<std::string> out;

        size_t start;
        size_t end = 0;

        while ((start = str.find_first_not_of(delim, end))
                      != std::string::npos)
        {
            end = str.find(delim, start);
            out.push_back(str.substr(start, end - start));
        }

        return out;
    }
}
