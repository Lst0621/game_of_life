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
        message("DIM: ${GOL_PY_DIM}")
        SET(lib_name "dim${GOL_PY_DIM}")
        message("creating ${lib_name}")


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

Build_GOL_PY_DIM(1)
Build_GOL_PY_DIM(2)
Build_GOL_PY_DIM(3)
Build_GOL_PY_DIM(4)
Build_GOL_PY_DIM(5)

add_custom_target(gol_py_script
        DEPENDS dim1 dim2 dim3 dim4 dim5
        COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/check_all_func.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../)
