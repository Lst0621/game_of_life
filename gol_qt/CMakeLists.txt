find_package(Qt5Widgets)
SET(gol_qt_src_files
        main.cpp
        GolWidget.h GolWidget.cpp
        )

add_executable(game_of_life_qt  ${gol_qt_src_files} )
target_link_libraries(game_of_life_qt gol_back glog Qt5::Widgets)