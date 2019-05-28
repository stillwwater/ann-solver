#include "config.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

namespace ann
{
namespace config
{

Level parse_level(const char* path, int n = 0) {
    Level level = { };
    int n_pos = 0;
    std::vector<char> buffer;
    std::fstream infile(path, std::fstream::in);

    char token;
    while (infile >> std::noskipws >> token) {
        if (token == ';') {
            n_pos++;
            continue;
        }

        if (n_pos != n) continue;
        if (token == '\n') {
            level.height++;
            continue;
        }
        buffer.push_back(token);
        if (level.height == 0) level.width++;
    }
    buffer.push_back('\0');

    level.data = std::string(buffer.begin(), buffer.end());
    return level;
}

} // namespace config
} // namespace ann
