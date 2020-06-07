#pragma once
#include <functional>
#include <string>
#include "Grid.h"
#include "VectorGrid.h"
namespace lst {
namespace gol {

template <int N>
class PlayGround {
   public:
    PlayGround(const typename Grid<N>::CoorType& size,
               std::function<typename Grid<N>::SharedGridPtr(
                   const typename Grid<N>::CoorType& size)>
                   factory = get_shared_pt<VectorGrid<N>>) {
        size_ = size;
        grid_ = factory(size);
        max_run_ = -1;
        set_up();
    };
    void run(std::function<void(typename Grid<N>::SharedGridPtr)> func =
                 [](typename Grid<N>::SharedGridPtr grid) {}) {
        // we allow -1
        constexpr int SameLimt = 100;

        int digest = grid_->get_digest();
        int s = grid_->sum();
        int& last_seen = digest_history[digest];

        if (last_seen != 0) {
            same_count = same_count + 1;
        } else {
            same_count = 0;
        }
        LOG(INFO) << "ep " << ep_ << " : live cells " << s << " digest "
                  << digest << " last seen " << last_seen;

        // todo move to another func
        func(getGrid());

        last_seen = ep_;
        LOG(INFO) << "evlove before";
        grid_->evolve();
        LOG(INFO) << "evlove after";
        ep_++;
        if (same_count == SameLimt) {
            LOG(INFO) << "Next";
            set_up();
        }
    }

    void set_up() {
        LOG(INFO) << "Playground set up";
        ep_ = 0;
        same_count = 0;
        digest_history.clear();
        // todo
        for (int i = 0; i < size_[0]; i++) {
            for (int j = 0; j < size_[1]; j++) {
                int n = rand() % 100;
                if (n < 30) {
                    grid_->set_cell({i, j}, Live);
                } else {
                    grid_->set_cell({i, j}, Dead);
                }
            }
        }
    }

   private:
    typename Grid<N>::CoorType size_;

   public:
    void set_max_run(int max_run) {
        max_run_ = max_run;
    }

   private:
    int max_run_;
    std::shared_ptr<Grid<N>> grid_;

    int same_count = 0;
    int ep_ = 0;
    std::unordered_map<int, int> digest_history;

   public:
    typename Grid<N>::SharedGridPtr getGrid() const {
        return grid_;
    }
};
}
}