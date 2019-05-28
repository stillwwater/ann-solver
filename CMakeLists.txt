cmake_minimum_required(VERSION 3.0)
project(solver)

include_directories(./src ./src/core)
add_executable(solver ./src/main.cc ./src/core/vector2.cc ./src/core/entity.cc ./src/core/room.cc ./src/config.cc ./src/engine.cc ./src/solver.cc)
target_link_libraries(solver)
