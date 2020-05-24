cmake_minimum_required(VERSION 3.10)

SET (CMAKE_C_COMPILER /usr/bin/clang)
SET (CMAKE_CXX_COMPILER /usr/bin/clang++)

project(game_of_life)

SET(CMAKE_CXX_STANDARD 17)

find_package(Qt5Widgets)

SET(src_files
        main.cpp
        Grid.h Grid.cpp
        Playground.h Playground.cpp
        GolWidget.h GolWidget.cpp
        )

add_executable(game_of_life  ${src_files} )
target_link_libraries(game_of_life glog Qt5::Widgets)
