#include <iostream>
#include "Grid.h"

using namespace lst::gol;
int main() {
    std::cout << "Hello, World!" << std::endl;
    Grid g(100, 100);
    g.set_cell(40, 40, Live);
    g.set_cell(41, 40, Live);
    g.set_cell(40, 41, Live);

    for (int i = 0; i < 40; i++) {
        std::cout << i << " " << g.sum() << std::endl;
        if (g.empty()) {
            break;
        }
        g = g.evolve();
    }

    return 0;
}
