#include <iostream>
#include "engine.h"
#include "config.h"

int main(int argc, char** argv) {
    auto level = Ann::Config::parse_level(argv[1], 0);
    auto room = Ann::Engine::create_room(level.data.c_str(), level.width, level.height);
    std::cout << Ann::Engine::serialize(room) << std::endl;
    Ann::Engine::pprint(room);
    Ann::Engine::exec(room, "rullurddlruuluu", true);
    Ann::Engine::print_state(room);

    std::cout.flush();
}