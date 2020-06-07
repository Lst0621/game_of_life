#pragma once

#include <map>
#include <set>
#include "glog/logging.h"

namespace lst {
namespace gol {
template <int N>
class VectorGrid : public Grid<N> {
   public:
   private:
    using BaseType = Grid<N>;
    std::set<typename BaseType::CoorType> cells_;
    std::vector<typename Grid<N>::CoorType> neighbours_shift =
        Grid<N>::get_neighbours(1);

   public:
    explicit VectorGrid(const typename Grid<N>::CoorType &size)
        : Grid<N>(size) {
        LOG(INFO) << "Hello from Vector Grid";
    }

    ~VectorGrid() {
        LOG(INFO) << "Bye from Vector Grid";
    }

    int get_digest() override {
        constexpr int weight = 3;
        constexpr int RES = 10000007;
        int sum = 0;
        for (const auto &coords : cells_) {
            for (const int &coord : coords) {
                sum = sum * weight + coord;
                sum = sum % RES;
            }
        }
        return sum;
        return 0;
    }

    bool empty() override {
        return cells_.empty();
    }

    int sum() const override {
        return cells_.size();
    }

    void evolve() override {
        constexpr int LiveLiveLower = 2;
        constexpr int LiveLiveHigher = 3;
        constexpr int DeadLiveLower = 3;
        constexpr int DeadLiveHigher = 3;
        std::set<typename BaseType::CoorType> next_cells;

        std::map<typename BaseType::CoorType, int> neighbour_cnt;
        for (const auto &cell : cells_) {
            for (const auto &shift : neighbours_shift) {
                typename BaseType::CoorType neighbour = cell;
                bool fit = true;
                for (int dim = 0; dim < N; dim++) {
                    neighbour[dim] += shift[dim];
                    if (neighbour[dim] < 0 ||
                        neighbour[dim] >= this->getSize()[dim]) {
                        fit = false;
                        break;
                    }
                }
                if (fit) {
                    neighbour_cnt[neighbour]++;
                }
            }
        }
        for (const auto &kv : neighbour_cnt) {
            auto pos = kv.first;
            bool current_live = cells_.count(pos);
            const int lower = current_live ? LiveLiveLower : DeadLiveLower;
            const int higher = current_live ? LiveLiveHigher : DeadLiveHigher;
            int neighbour_sum = kv.second;
            if (current_live) {
                neighbour_sum--;
            }
            if (neighbour_sum >= lower && neighbour_sum <= higher) {
                next_cells.insert(pos);
            }
        }
        cells_ = std::move(next_cells);
    }

    bool set_cell(const typename BaseType::CoorType &coor, int value) override {
        if (!this->check_cell_valid(coor)) {
            return false;
        }
        if (value == Live) {
            cells_.insert(coor);
        } else {
            cells_.erase(coor);
        }
        return true;
    }

    void to_console(char ch) const override {
    }

    std::vector<typename Grid<N>::CoorType> get_live_cells() const override {
        return {cells_.begin(), cells_.end()};
    }
};
}
}
