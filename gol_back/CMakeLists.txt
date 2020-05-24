SET(gol_back_src_files
        Grid.h Grid.cpp
        Playground.h Playground.cpp
        )
add_library(gol_back SHARED ${gol_back_src_files}  )
