#include <iostream>
#include <set>
#include <queue>
#include <string>
#include "entity.h"
#include "engine.h"
#include "room.h"
#include "solver.h"

namespace ann
{
namespace solver
{

Info solve(Room* room, bool log) {
    const char dirs[4] = {'u', 'r', 'l', 'd'};
    std::queue<Room*> open;
    std::set<size_t> visited;
    Info info = {};

    int prev_size;
    open.push(new Room(room));

    while (open.size() > 0) {
        room = open.front();
        int bfactor = 0;
        open.pop();

        for (int i = 0; i < 4; i++) {
            info.trials++;
            auto trial = new Room(room);
            bool did_move = engine::move(trial, dirs[i]);

            if (trial->state == Room::Fail) {
                delete trial;
                bfactor++;
                info.fail_states++;
                continue;
            }

            if (!did_move) {
                delete trial;
                continue;
            }

            size_t trial_hash = engine::hash(trial);

            if (visited.find(trial_hash) == visited.end()) {
                bfactor++;
                trial->solution.push_back(dirs[i]);
                open.push(trial);
                visited.insert(trial_hash);

                if (trial->state == Room::Pass) {
                    info.solution = trial->solution;
                    while (open.size() > 0) {
                        delete open.front();
                        open.pop();
                    }
                    info.solved = true;
                    return info;
                }
                continue;
            }
            delete trial;
        }

        info.states++;
        info.open = open.size();
        info.bfactor = bfactor;
        prev_size = open.size();

        if (info.open > info.peak)
            info.peak = info.open;

        info.avg_bf = (info.avg_bf + info.bfactor) / 2.0;

        if (log) {
            info.solution = room->solution;
            log_info(info);
            engine::pprint(room);
        }

        delete room;
    }

    info.solution = "No solution";
    return info;
}

void log_info(const Info& info) {
    std::cout << "trials  : " << info.trials << std::endl;
    std::cout << "states  : " << info.states << std::endl;
    std::cout << "failed  : " << info.fail_states << std::endl;
    std::cout << "peak    : " << info.peak << std::endl;
    std::cout << "open    : " << info.open << std::endl;
    std::cout << "bfactor : " << info.bfactor << std::endl;
    std::cout << "avg_bf  : " << info.avg_bf << std::endl;
    std::cout << info.solution << std::endl;
}

} // namespace solver
} // namespace ann
