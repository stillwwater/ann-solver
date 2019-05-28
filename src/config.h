#ifndef _ANN_CONFIG
#define _ANN_CONFIG

#include <string>

namespace ann
{
namespace config
{

struct Level
{
    int width, height;
    std::string data;
};

Level parse_level(const char* path, int n);

} // namespace config
} // namespace ann

#endif
