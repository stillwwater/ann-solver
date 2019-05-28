#ifndef _ANN_SOLVER
#define _ANN_SOLVER

#include <string>
#include "room.h"

namespace ann
{
namespace solver
{

struct Info
{
    int states;
    int fail_states;
    int trials;
    int bfactor;
    int open;
    int peak;
    double avg_bf;
    bool solved;
    std::string solution;
};

void log_info(const Info& info);
Info solve(Room* room, bool log);

} // namespace solver
} // namespace ann

#endif
