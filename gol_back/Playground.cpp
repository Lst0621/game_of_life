#include "Playground.h"

#include <glog/logging.h>
#include <unistd.h>
#include <iostream>
#include <unordered_map>
namespace lst {
namespace gol {
PlayGround::PlayGround(int width, int height)
    : width_(width), height_(height), grid_(Grid(width, height)) {
    max_run_ = -1;
    set_up();
}

void PlayGround::run(std::function<void(const Grid &)> func) {
    // we allow -1
    constexpr int SameLimt = 100;

    int digest = grid_.get_digest();
    int s = grid_.sum();
    int &last_seen = digest_history[digest];

    if (last_seen != 0) {
        same_count = same_count + 1;
    } else {
        same_count = 0;
    }
    LOG(INFO) << "ep " << ep_ << " : live cells " << s << " digest " << digest
              << " last seen " << last_seen;

    // todo move to another func
    func(getGrid());

    /**
    grid_.to_console();
    usleep(1000 * epoch_);
    system("clear");
    **/

    last_seen = ep_;
    LOG(INFO) << "evlove before";
    grid_ = grid_.evolve();
    LOG(INFO) << "evlove after";
    ep_++;
    if (same_count == SameLimt) {
        LOG(INFO) << "Next";
        set_up();
    }
}

void PlayGround::set_up() {
    ep_ = 0;
    same_count = 0;
    digest_history.clear();
    for (int i = 0; i < width_; i++) {
        for (int j = 0; j < height_; j++) {
            int n = rand() % 100;
            if (n < 30) {
                grid_.set_cell(i, j, Live);
            } else {
                grid_.set_cell(i, j, Dead);
            }
        }
    }
}

void PlayGround::setMaxRun(int maxRun) {
    max_run_ = maxRun;
}

const Grid &PlayGround::getGrid() const {
    return grid_;
}
}
}
