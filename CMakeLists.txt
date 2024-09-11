cmake_minimum_required(VERSION 3.29)
project(troll)

set(CMAKE_CXX_STANDAR 20)

add_executable(troll src/main.cpp src/board.hpp src/board.cpp src/player.hpp src/player.cpp src/game.hpp src/game.cpp)