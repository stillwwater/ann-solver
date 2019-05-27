#ifndef _ANN_CONFIG
#define _ANN_CONFIG

#include <string>

namespace Ann
{
namespace Config
{

struct Level
{
    int width, height;
    std::string data;
};

Level parse_level(const char* path, int n);

} // namespace Config
} // namespace Ann

#endif