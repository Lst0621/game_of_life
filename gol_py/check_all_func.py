# run in cmake
# cwd is set to ${CMAKE_CURRENT_BINARY_DIR
import os
import sys

sys.path.append(os.getcwd())
print(os.getcwd())
import gol_py


# todo move to cpp?
def gen_coor(x,y):
    sz = gol_py.CoorType()
    sz.set( 0,  x)
    sz.set( 1, y)
    return sz

def t_playground():
    print("test playground...")
    pl = gol_py.PlayGround(gen_coor(8,8))
    print(type(pl))
    num_iter = 5
    for i in range(num_iter):
        pl.run()
        grid = pl.getGrid()
        print(type(grid))
        print(grid.sum(), grid.get_digest())
        coords = grid.get_live_cells()
        print(len(coords), type(coords))


def t_grid():
    print("test grid...")

    #grid = gol_py.Grid2DVec(gen_coor(4,4))
    grid = gol_py.Grid2DVectorPtr(gen_coor(4,4))
    print(grid.sum(), grid.get_digest())
    grid.set_cell(gen_coor(0,0), 1)
    print(grid.sum(), grid.get_digest())
    coords = grid.get_live_cells()
    print(len(coords), type(coords))


def t_coord():
    print("test coord...")
    co = gol_py.CoorType()
    print("Coord dim: {} {}".format(len(co), co.size()))
    print("Value at start: {} {}".format(co.get(0), co.get(1)))
    co.set(0, 1)
    co.set(1, 1)
    print("Value should be changed: {} {}".format(co.get(0), co.get(1)))



def main():
    t_coord()
    print()
    t_grid()
    print()
    t_playground()
    print()


if __name__ == '__main__':
    main()
