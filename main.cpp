#include <iostream>
#include "Playground.h"

using namespace lst::gol;
int main() {
    std::cout << "Game of Life" << std::endl;
    int h = 70;
    int w = 50;
    PlayGroud pg = PlayGroud(w, h);
    pg.setVisual();
    while (true) {
        pg.set_up();
        pg.run();
    }

    return 0;
}
