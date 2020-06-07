#pragma once
#include <array>
#include <memory>
#include <vector>
#include "glog/logging.h"

namespace lst {
namespace gol {
static constexpr int Live = 1;
static constexpr int Dead = 0;

template <int N>
class Grid {
   public:
    static constexpr int DIM = N;
    using BaseGridT = Grid<DIM>;
    using CoorType = std::array<int, N>;
    Grid(const CoorType& size) {
        size_ = size;
        LOG(INFO) << "Hello from Grid";
    }
    using SharedGridPtr = std::shared_ptr<Grid>;

    virtual int get_digest() = 0;
    virtual bool empty() = 0;
    [[nodiscard]] virtual int sum() const = 0;
    // virtual SharedGridPtr evolve() = 0;
    virtual void evolve() = 0;
    virtual bool set_cell(const CoorType& coor, int value) = 0;
    virtual void to_console(char ch = '#') const = 0;
    virtual std::vector<CoorType> get_live_cells() const = 0;
    virtual ~Grid() {
        LOG(INFO) << "Bye from Grid";
    }
    virtual bool check_cell_valid(const CoorType& coor) {
        // todo use algo
        for (int dim = 0; dim < N; dim++) {
            if (coor[dim] < 0 || coor[dim] >= size_[dim]) {
                return false;
            }
        }
        return true;
    }
    inline static std::vector<CoorType> get_neighbours(int dist);

   protected:
    // int width_;
    // int height_;
    CoorType size_;

   public:
    const CoorType& getSize() const {
        return size_;
    }
    // using DataType = std::vector<std::vector<char>>;
    // DataType data_;
    // bool is_valid_xy(CoorType coord ) const;
    // int get_neighbour_sum(int x, int y) const;
};

template <int N>
inline std::vector<typename Grid<N>::CoorType> Grid<N>::get_neighbours(
    int dist) {
    auto lower_dim = Grid<N - 1>::get_neighbours(dist);
    std::vector<typename Grid<N>::CoorType> ret;
    for (const auto& lower_dim_result : lower_dim) {
        for (int i = -dist; i <= dist; i++) {
            typename Grid<N>::CoorType coor;
            for (int dim = 0; dim < N - 1; dim++) {
                coor[dim] = lower_dim_result[dim];
            }
            coor[N - 1] = i;
            ret.push_back(coor);
        }
    }
    return ret;
}
template <>
inline std::vector<typename Grid<1>::CoorType> Grid<1>::get_neighbours(
    int dist) {
    std::vector<typename Grid<1>::CoorType> ret;
    for (int i = -dist; i <= dist; i++) {
        typename Grid<1>::CoorType coor;
        coor[0] = i;
        ret.push_back(coor);
    }
    return ret;
}
template <class GridImpl>
typename Grid<GridImpl::DIM>::SharedGridPtr get_shared_pt(
    const typename GridImpl::CoorType& size) {
    static_assert(std::is_base_of<Grid<GridImpl::DIM>, GridImpl>::value);
    return std::make_shared<GridImpl>(size);
}
};
};