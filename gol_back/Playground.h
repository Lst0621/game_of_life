#pragma once
#include <functional>
#include <string>

#include "Grid.h"
namespace lst {
namespace gol {
class PlayGround {
   public:
    PlayGround(int width, int height);
    void run(std::function<void(const Grid &)> func = [](const Grid &grid) {});
    void set_up();

   private:
    int width_;
    int height_;

   public:
    void setVisual();

    void setMaxRun(int maxRun);

    void setEpoch(int epoch);

   private:
    int max_run_;
    Grid grid_;

    int same_count = 0;
    int ep_ = 0;
    std::unordered_map<int, int> digest_history;

   public:
    const Grid &getGrid() const;
};
}
}