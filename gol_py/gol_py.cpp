#include <boost/python.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/suite/indexing/indexing_suite.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "Playground.h"

#include "gol_py.h"
using namespace boost::python;
using namespace lst::gol;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(playground_run_overload, PlayGround::run,
                                       0, 1)

// cannot find a way to directly use at or [] func yet
using Grid2DVector = VectorGrid<2>;
using Grid2DBase = Grid<2>;
using Grid2DVectorPtrWrapper = GridImplPt<Grid2DVector>;
using PlayGround2D = PlayGround<2>;

int coor_get(Grid2DBase::CoorType& coor, size_t pos) {
    return coor[pos];
}
void coor_set(Grid2DBase::CoorType& coor, size_t pos, int value) {
    coor[pos] = value;
}

BOOST_PYTHON_MODULE(gol_py) {
    class_<Grid2DBase::CoorType>("CoorType")
        .def("size", &Grid<2>::CoorType::size)
        .def("__len__", &Grid<2>::CoorType::size)
        .def("get", coor_get)
        .def("set", coor_set);

    class_<std::vector<Grid2DBase::CoorType>>("CordList")
        .def((vector_indexing_suite<std::vector<Grid2DVector::CoorType>>()));

    class_<Grid2DBase, std::shared_ptr<Grid2DBase>, boost::noncopyable>(
        "Grid2DBasePtr", no_init);

    class_<Grid2DVector, bases<Grid2DBase>, std::shared_ptr<Grid2DVector>>(
        "Grid2DVectorPtr", init<Grid2DVector::CoorType>())
        .def("sum", &Grid2DVectorPtrWrapper::sum)
        .def("get_digest", &Grid2DVectorPtrWrapper::get_digest)
        .def("get_live_cells", &Grid2DVectorPtrWrapper::get_live_cells,
             boost::python::return_value_policy<
                 boost::python::return_by_value>())
        .def("set_cell", &Grid2DVectorPtrWrapper::set_cell)
        .def("evolve", &Grid2DVectorPtrWrapper::evolve);

    class_<PlayGround2D>("PlayGround", init<Grid2DVector::CoorType>())
        .def("set_up", &PlayGround2D::set_up)
        .def("getGrid", &PlayGround2D::getGrid)
        .def("run", &PlayGround2D::run, playground_run_overload());
}
