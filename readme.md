# Game Of Life
## Intro
The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970.

This is a c++ implementation with optional qt visualization and python wrapper. 


## Rules
* Any live cell with two or three live neighbours survives.
* Any dead cell with three live neighbours becomes a live cell.
* All other live cells die in the next generation. Similarly, all other dead cells stay dead.

## Implementation
With c++ template, user defined dimension number is supported.

## Dependencies
### Better to have
* glog: or change to cout
### For specific build
* qt5-default: for visualization
* qt3d5-dev
* qt3d-assimpsceneimport-plugin
* qt3d-defaultgeometryloader-plugin 
* qt3d-gltfsceneio-plugin
* qt3d-scene2d-plugin

* libboost-python-dev: for py wrapper

## Build
In project folder

    makedir cmake-build-release && cd cmake-build-release
    cmake ..
    make -j
    # run py script
    make gol_py_script
   
## Ref
https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
