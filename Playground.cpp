#include "Playground.h"

#include <glog/logging.h>
#include <unistd.h>
#include <iostream>
#include <unordered_map>
namespace lst {
namespace gol {

PlayGroud::PlayGroud(int width, int height)
    : width_(width), height_(height), grid_(Grid(width, height)) {
    max_run_ = -1;
    visual_ = false;
    epoch_ = 100;
}

void PlayGroud::run() {
    // we allow -1
    int same_count = 0;
    constexpr int SameLimt = 100;

    std::unordered_map<int, int> digest_history;
    for (int i = 0; i != max_run_; i++) {
        if (visual_) {
            grid_.to_console();
            int digest = grid_.get_digest();
            int s = grid_.sum();
            int &last_seen = digest_history[digest];

            if (last_seen != 0) {
                same_count = same_count + 1;
            } else {
                same_count = 0;
            }
            LOG(INFO) << "ep " << i << " : live cells " << s
                      << " digest " << digest << " last seen " << last_seen;
            usleep(1000 * epoch_);
            system("clear");
            last_seen = i;
        }
        grid_ = grid_.evolve();
        if (same_count == SameLimt) {
            LOG(INFO) << "Next";
            break;
        }
    }
}

void PlayGroud::set_up() {
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

void PlayGroud::setVisual() {
    visual_ = true;
}

void PlayGroud::setMaxRun(int maxRun) {
    max_run_ = maxRun;
}

void PlayGroud::setEpoch(int epoch) {
    epoch_ = epoch;
}
}
}
