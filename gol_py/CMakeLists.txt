find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# get boost
find_package(Boost COMPONENTS
        python3
        REQUIRED)
message("boost: ${Boost_LIBRARIES}")

SET(gol_py_src_files
        gol_py.cpp
        )
add_library(gol_py SHARED ${gol_py_src_files})

target_link_libraries(gol_py gol_back glog  ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} )
  # Tweaks the name of the library to match what Python expects
set_target_properties(gol_py PROPERTIES SUFFIX .so)
set_target_properties(gol_py PROPERTIES PREFIX "")

add_custom_target (gol_py_script
        DEPENDS gol_py
        COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/check_all_func.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/)
