#include <iostream>
#include <string>
#include "engine.h"
#include "config.h"
#include "solver.h"

int main(int argc, char** argv) {
    auto level = Ann::Config::parse_level(argv[1], 0);
    auto room = Ann::Engine::create_room(level.data.c_str(), level.width, level.height);
    std::cout << Ann::Solver::solve(room, true).solution << std::endl;
    std::cout.flush();
}
