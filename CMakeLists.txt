cmake_minimum_required(VERSION 3.10)

SET (CMAKE_C_COMPILER /usr/bin/clang)
SET (CMAKE_CXX_COMPILER /usr/bin/clang++)

project(game_of_life)

SET(CMAKE_CXX_STANDARD 17)
SET(src_files
        main.cpp
        Grid.h Grid.cpp
        )

add_executable(game_of_life  ${src_files})