#pragma once
#include "Playground.h"

namespace lst {
namespace gol {

template <int N>
int coor_get(typename Grid<N>::CoorType& coor, size_t pos) {
    return coor[pos];
}

template <int N>
void coor_set(typename Grid<N>::CoorType& coor, size_t pos, int value) {
    coor[pos] = value;
}

template <template <int M> class GridImpl, int N>
class GridImplPt {
   public:
    static_assert(std::is_base_of<Grid<N>, GridImpl<N>>::value);
    using PtType = std::shared_ptr<GridImpl<N>>;
    using CoorType = typename Grid<N>::CoorType;

    static int sum(PtType pt) {
        return pt->sum();
    }

    static int get_digest(PtType pt) {
        return pt->get_digest();
    }

    static void evolve(PtType pt) {
        return pt->evolve();
    }

    static bool set_cell(PtType pt, const CoorType& coor, int value) {
        return pt->set_cell(coor, value);
    }

    static std::vector<CoorType> get_live_cells(PtType pt) {
        return pt->get_live_cells();
    }
};
}  // namespace gol
}  // namespace lst