#include <boost/python.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/suite/indexing/indexing_suite.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "Playground.h"
using namespace boost::python;
using namespace lst::gol;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(playground_run_overload, PlayGround::run,
                                       0, 1)

// cannot find a way to directly use at or [] func yet
int coor_get(Grid::CoorType& coor, size_t i) {
    return coor[i];
}
void coor_set(Grid::CoorType& coor, size_t i, int value) {
    coor[i] = value;
}

// std::function<const int&(size_t)> fooooo = &bar::at;
BOOST_PYTHON_MODULE(gol_py) {
    class_<Grid::CoorType>("CoorType")
        .def("size", &Grid::CoorType::size)
        .def("__len__", &Grid::CoorType::size)
        .def("get", coor_get)
        .def("set", coor_set);

    class_<std::vector<Grid::CoorType>>("CordList")
        .def((vector_indexing_suite<std::vector<Grid::CoorType>>()));

    class_<Grid>("Grid", init<int, int>())
        .def("get_digest", &Grid::get_digest)
        .def("sum", &Grid::sum)
        .def("get_live_cells", &Grid::get_live_cells,
             boost::python::return_value_policy<
                 boost::python::return_by_value>())
        .def("set_cell", &Grid::set_cell)
        .def("evolve", &Grid::evolve);

    class_<PlayGround>("PlayGround", init<int, int>())
        .def("set_up", &PlayGround::set_up)
        .def("getGrid", &PlayGround::getGrid, return_internal_reference<>())
        .def("run", &PlayGround::run, playground_run_overload());
}
