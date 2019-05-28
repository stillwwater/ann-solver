cmake_minimum_required(VERSION 3.0)
project(solver)

include_directories(./src)
add_executable(solver ./src/main.cc ./src/vector2.cc ./src/entity.cc ./src/room.cc ./src/config.cc ./src/engine.cc ./src/solver.cc)
target_link_libraries(solver)
