#ifndef _ANN_CONFIG
#define _ANN_CONFIG

#include <string>

namespace ann
{
namespace config
{

struct Options
{
    bool abort;
    char* filename;
    int level_id;
    bool verbose;
    bool show_stats;
    int delay_ms;
    bool run_solution;
    char* solution_text;
};

struct Level
{
    int width, height;
    std::string data;
};

Options parse_cli_args(int argc, char** argv);
Level parse_level(const char* path, int n);

} // namespace config
} // namespace ann

#endif
