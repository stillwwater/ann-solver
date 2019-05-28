#include <iostream>
#include <string>
#include <vector>
#include "room.h"
#include "engine.h"
#include "config.h"
#include "solver.h"

void run_solver(ann::Room* room, const ann::config::Options& opt) {
    auto solver_info = ann::solver::solve(room, opt.verbose, opt.delay_ms);

    if (opt.show_stats) {
        ann::solver::log_info(solver_info);
        std::cout << std::endl;
    }

    std::cout << "solutions: " << solver_info.solutions.size() << std::endl;
    for (auto solution : solver_info.solutions) {
        std::cout << "(" << solution.length() << ") ";
        std::cout << solution << std::endl;
    }
}

void run_solution(ann::Room* room, const ann::config::Options& opt) {
    ann::engine::exec(room, opt.solution_text, opt.verbose);
    std::cout << opt.solution_text << std::endl;
    if (room->state == ann::Room::Pass) {
        std::cout << "passed" << std::endl;
        return;
    }
    std::cout << "failed" << std::endl;
}

void print_help(void) {
    const char* help = "Usage\n\n"
                       "  solver [options] -i <path-to-level>\n\n"
                       "Options\n"
                       "  -d              : Delay (ms) between solver states\n"
                       "  -l <level-id>   : Level id in source file\n"
                       "  -s              : Show statistics from the solver\n"
                       "  -t <solution>   : Test a solution on a level\n"
                       "  -v              : Verbose output\n";
    std::cout << help << std::endl;
}

int main(int argc, char** argv) {
    auto opt = ann::config::parse_cli_args(argc, argv);

    if (opt.abort) {
        print_help();
        return 1;
    }

    auto level = ann::config::parse_level(opt.filename, opt.level_id);
    auto room = ann::engine::create_room(level.data.c_str(), level.width, level.height);

    ann::engine::pprint(room);

    if (opt.run_solution) {
        run_solution(room, opt);
        return 0;
    }
    run_solver(room, opt);

    return 0;
}
