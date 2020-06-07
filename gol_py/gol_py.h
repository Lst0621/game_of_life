#pragma once
#include "Playground.h"

namespace lst {
namespace gol {

template <class GridImpl>
class GridImplPt {
   public:
    static_assert(std::is_base_of<Grid<GridImpl::DIM>, GridImpl>::value);
    using PtType = std::shared_ptr<GridImpl>;

    static int sum(PtType pt) {
        return pt->sum();
    }

    static int get_digest(PtType pt) {
        return pt->get_digest();
    }

    static void evolve(PtType pt) {
        return pt->evolve();
    }

    static bool set_cell(PtType pt, const typename GridImpl::CoorType &coor,
                         int value) {
        return pt->set_cell(coor, value);
    }

    static std::vector<typename GridImpl::CoorType> get_live_cells(PtType pt) {
        return pt->get_live_cells();
    }
};
}
}