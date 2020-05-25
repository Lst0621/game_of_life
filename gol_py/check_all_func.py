# run in cmake
# cwd is set to ${CMAKE_CURRENT_BINARY_DIR
import os
import sys
sys.path.append(os.getcwd())
print(os.getcwd())
import gol_py


def main():
	pl = gol_py.PlayGround(10,10)
	num_iter = 10
	for i in range(num_iter):
		pl.run()


if __name__ == '__main__':
	main()
