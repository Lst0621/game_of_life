# run in cmake
# cwd is set to ${CMAKE_CURRENT_BINARY_DIR
import os
import sys
sys.path.append(os.getcwd())
print(os.getcwd())
import gol_py


def t_playground():
    print("test playground...")
    pl = gol_py.PlayGround(8,8)
    print(type(pl))
    num_iter = 4
    for i in range(num_iter):
        pl.run()
        grid = pl.getGrid()
        print(grid.sum(),grid.get_digest())
        coords = grid.get_live_cells()
        print(len(coords),type(coords))
    print()


def t_grid():
    print("test grid...")
    grid = gol_py.Grid(4,4)
    print(grid.sum(),grid.get_digest())
    grid.set_cell(0,0,1)
    print(grid.sum(),grid.get_digest())
    print()

def t_coord():
    print("test coord")
    co = gol_py.CoorType()
    print("Coord dim: {} {}".format(len(co),co.size()))
    print( "Value at start: {} {}".format(co.get(0),co.get(1)))
    co.set(0,1)
    co.set(1,1)
    print( "Value should be changed: {} {}".format(co.get(0),co.get(1)))
    print()

def main():
    t_coord()
    t_grid()
    t_playground()

if __name__ == '__main__':
    main()
