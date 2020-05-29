cmake_minimum_required(VERSION 3.10)

SET (CMAKE_C_COMPILER /usr/bin/clang)
SET (CMAKE_CXX_COMPILER /usr/bin/clang++)

project(game_of_life)

SET(CMAKE_CXX_STANDARD 17)
include_directories(gol_back_inc)

add_subdirectory(gol_back)
add_subdirectory(gol_py)

