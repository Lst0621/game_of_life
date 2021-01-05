find_package(Qt5Widgets)
find_package(Qt53DCore)
find_package(Qt53DExtras REQUIRED)
#find_package(Qt53DRender)
#find_package(Qt53DCore)
#find_package(Qt53DCore)
SET(gol_qt_src_files
        main.cpp
        GolWidget.h GolWidget.cpp
        )

add_executable(game_of_life_qt  ${gol_qt_src_files} )
target_link_libraries(game_of_life_qt gol_back glog Qt5::Widgets Qt5::3DCore Qt5::3DExtras  )