#include <iostream>
#include <string>
#include <vector>
#include "engine.h"
#include "config.h"
#include "solver.h"

int main(int argc, char** argv) {
    auto level = ann::config::parse_level(argv[1], 0);
    auto room = ann::engine::create_room(level.data.c_str(), level.width, level.height);

    auto solver_info = ann::solver::solve(room, true);
    std::cout << "solutions: " << solver_info.solutions.size() << std::endl;

    if (solver_info.solutions.size() < 1) {
        std::cout << "No solution" << std::endl;
    }

    for (auto solution : solver_info.solutions) {
        std::cout << "(" << solution.length() << ") ";
        std::cout << solution << std::endl;
    }

    std::cout.flush();
}
