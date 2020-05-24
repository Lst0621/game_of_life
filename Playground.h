#pragma once
#include <string>

#include "Grid.h"
namespace lst {
namespace gol {
class PlayGroud {
   public:
    PlayGroud(int width, int height);
    void run();
    void set_up();

   private:
    int width_;
    int height_;
    bool visual_;

   public:
    void setVisual();

    void setMaxRun(int maxRun);

    void setEpoch(int epoch);

   private:
    int max_run_;
    int epoch_;
    Grid grid_;

   public:
    void setOutFn(const std::string &outFn);
};
}
}