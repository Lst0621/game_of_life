# run in cmake
# cwd/pwd is set to ${CMAKE_CURRENT_BINARY_DIR

import os
import sys
import importlib

################## Import GOL Package ##################
current_path = os.getcwd()
sys.path.append(current_path)
print("pwd: {}".format(current_path))

# DIM is set here
dim_number = 3
gol_py_package_name = 'gol_py.dim{}'.format(dim_number, dim_number)
print("package to import: {}".format(gol_py_package_name))

gol_py_package = importlib.import_module(gol_py_package_name)

CoorType = gol_py_package.CoorType
CordList = gol_py_package.CordList
GridVectorPtr = gol_py_package.GridVectorPtr
PlayGround = gol_py_package.PlayGround

################## Helper ##################

def gen_coor(inputs):
    sz = CoorType()
    dim = len(sz)
    for i, num in enumerate(inputs):
        if i == dim:
            break
        sz.set(i, num)
    return sz


def gen_coor_all(x):
    sz = CoorType()
    for i in range(len(sz)):
        sz.set(i, x)
    return sz


################## Testing Functions ##################

def extra_print(func):
    def wrapper():
        char_cnt = 60
        div_char = '-'
        print()
        print(div_char * char_cnt)
        func()
        print(div_char * char_cnt)
        print()

    return wrapper


@extra_print
def t_playground():
    print("test playground...")
    init_size = 10
    num_iter = 2
    pl = PlayGround(gen_coor_all(init_size))
    print(type(pl))
    for i in range(num_iter):
        pl.run()
        grid = pl.getGrid()
        if i == 0:
            print(type(grid))
        coords = grid.get_live_cells()
        print("iter {}: live cells {} , digest: {}".format(i, grid.sum(), grid.get_digest()))


@extra_print
def t_grid():
    print("test grid...")

    grid = GridVectorPtr(gen_coor_all(4))
    print("grid sum and digest: {} {}".format(grid.sum(), grid.get_digest()))
    grid.set_cell(gen_coor_all(0), 1)
    print("grid sum and digest: {} {}".format(grid.sum(), grid.get_digest()))
    coords = grid.get_live_cells()
    print("coord list len: {}  ,type: {}".format(len(coords), type(coords)))
    grid.set_cell(gen_coor_all(1), 1)
    print("grid sum and digest: {} {}".format(grid.sum(), grid.get_digest()))
    coords = grid.get_live_cells()
    print("coord list len: {}  ,type: {}".format(len(coords), type(coords)))


@extra_print
def t_coord():
    print("test coord...")
    co = CoorType()
    dim = len(co)
    print("Coord dim: {} {}".format(len(co), co.size()))
    print("Value start: {}".format(",".join([str(co.get(i)) for i in range(dim)])))
    for i in range(dim):
        co.set(i, 1)
    print("Value changed: {}".format(",".join([str(co.get(i)) for i in range(dim)])))


################## Main ##################
def main():
    t_coord()
    t_grid()
    t_playground()


if __name__ == '__main__':
    main()
