find_package(PythonInterp 3 REQUIRED)
message("python inc: ${PYTHON_INCLUDE_DIRS}")
find_package(PythonLibs 3 REQUIRED)
message("python inc: ${PYTHON_INCLUDE_DIRS}")
include_directories(${PYTHON_INCLUDE_DIRS})

# get boost
find_package(Boost COMPONENTS
        python3
        REQUIRED)
message("boost: ${Boost_LIBRARIES}")


function(Build_GOL_PY_DIM GOL_PY_DIM)
    SET(lib_name "dim${GOL_PY_DIM}")
    List(APPEND py_lib_list ${lib_name})
    SET(py_lib_list ${py_lib_list} PARENT_SCOPE)

    message("Creating ${lib_name}")

    SET(gol_py_src_files
            gol_py.cpp
            )
    add_library(${lib_name} SHARED ${gol_py_src_files})

    target_compile_definitions(${lib_name} PUBLIC -DPY_WRAPPER_DIM=${GOL_PY_DIM})
    target_compile_definitions(${lib_name} PUBLIC -DLIB_NAME=${lib_name})

    target_link_libraries(${lib_name} gol_back glog ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

    # Tweaks the name of the library to match what Python expects
    set_target_properties(${lib_name} PROPERTIES SUFFIX .so)
    set_target_properties(${lib_name} PROPERTIES PREFIX "")

    remove_definitions(-DPY_WRAPPER_DIM)
    remove_definitions(-DLIB_NAME)

endfunction()


foreach (dimension RANGE 1 ${GOL_MAX_DIM})
    Build_GOL_PY_DIM(${dimension})
endforeach ()

message("\nAll Dims: ${py_lib_list}")

add_custom_target(gol_py_script
        DEPENDS ${py_lib_list}
        COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/check_all_func.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../)
