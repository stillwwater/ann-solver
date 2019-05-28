#include "config.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

namespace ann
{
namespace config
{

Options parse_cli_args(int argc, char** argv) {
    Options options = {};
    if (argc <= 1) {
        options.abort = true;
        return options;
    }

    char flag;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            flag = argv[i][1];
        }
        switch (flag) {
            case 'i':
                options.filename = argv[++i];
                break;
            case 'l':
                options.level_id = std::atoi(argv[++i]);
                break;
            case 'v':
                options.verbose = true;
                break;
            case 't':
                options.run_solution = true;
                options.solution_text = argv[++i];
                break;
            case 'd':
                options.delay_ms = std::atoi(argv[++i]);
                break;
            case 's':
                options.show_stats = true;
                break;
            default:
                options.abort = true;
                return options;
        }
    }
    return options;
}

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
