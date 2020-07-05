add_custom_target(gen_pre_compile
        COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/gen_pre_compile.py ${GOL_MAX_DIM}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

SET(gol_back_src_files
        Playground.cpp
        )
add_library(gol_back SHARED ${gol_back_src_files})
add_dependencies(gol_back gen_pre_compile)
