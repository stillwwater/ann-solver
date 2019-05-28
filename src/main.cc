#include <iostream>
#include <string>
#include "engine.h"
#include "config.h"
#include "solver.h"

int main(int argc, char** argv) {
    auto level = ann::config::parse_level(argv[1], 0);
    auto room = ann::engine::create_room(level.data.c_str(), level.width, level.height);
    std::cout << ann::solver::solve(room, true).solution << std::endl;
    std::cout.flush();
}
