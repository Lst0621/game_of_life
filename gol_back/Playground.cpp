#include "Playground.h"
#include "Grid.h"
#include "VectorGrid.h"
namespace lst {
namespace gol {

template std::shared_ptr<Grid<2>> get_shared_pt<VectorGrid<2>>(
    const typename Grid<2>::CoorType& size);
template class VectorGrid<2>;
template class PlayGround<2>;
}
}
