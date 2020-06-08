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
    PlayGround(const typename Grid<N>::CoorType &size,
               std::function<typename Grid<N>::SharedGridPtr(
                   const typename Grid<N>::CoorType &size)>
                   factory = get_shared_pt<VectorGrid<N>>) {
        size_ = size;
        grid_ = factory(size);
        max_run_ = -1;
        same_limit_ = 100;
        set_up();
    };
    virtual void run(std::function<void(typename Grid<N>::SharedGridPtr)> func =
                         [](typename Grid<N>::SharedGridPtr grid) {}) {
        int digest = grid_->get_digest();
        int s = grid_->sum();
        int &last_seen = digest_history[digest];

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
        if (same_count == same_limit_) {
            LOG(INFO) << "Next";
            set_up();
        }
    }
    void set_up() {
        LOG(INFO) << "Playground set up";
        clear();
        init_grid();
        LOG(INFO) << "Playground set done";
    }

   private:
    void clear() {
        LOG(INFO) << "Playground clear...";
        ep_ = 0;
        same_count = 0;
        digest_history.clear();
        grid_->clear();
    }

    // Just to test template, current dim as a function para also works
    template <int CurrentDim>
    void get_starting_live_cells_helper(
        std::vector<typename Grid<N>::CoorType> &vec,
        typename Grid<N>::CoorType &pt) {
        for (int i = 0; i < size_[CurrentDim]; i++) {
            pt[CurrentDim] = i;
            if
                constexpr(CurrentDim == N - 1) {
                    int n = rand() % 100;
                    if (n < 30) {
                        vec.push_back(pt);
                    }
                }
            else {
                get_starting_live_cells_helper<CurrentDim + 1>(vec, pt);
            }
        }
    }

    std::vector<typename Grid<N>::CoorType> get_starting_live_cells() {
        std::vector<typename Grid<N>::CoorType> ret;
        typename Grid<N>::CoorType pt;
        get_starting_live_cells_helper<0>(ret, pt);
        return ret;
    }

    void init_grid() {
        const auto vec = get_starting_live_cells();
        grid_->set_cell_from_container(vec, Live);
    }

    typename Grid<N>::CoorType size_;

   public:
    void set_max_run(int max_run) {
        max_run_ = max_run;
    }
    void setSameLimit(int sameLimit) {
        same_limit_ = sameLimit;
    }

   private:
    int max_run_;
    std::shared_ptr<Grid<N>> grid_;

    int same_count = 0;
    int ep_ = 0;
    int same_limit_ = 0;

   private:
    std::unordered_map<int, int> digest_history;

   public:
    virtual ~PlayGround() {
        LOG(INFO) << "Bye from Playground";
    }

    typename Grid<N>::SharedGridPtr getGrid() const {
        return grid_;
    }
};
}  // namespace gol
}  // namespace lst