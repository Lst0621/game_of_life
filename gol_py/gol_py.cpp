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

std::string get_type_str(const std::string& name, int dim) {
    return std::string(name + std::to_string(dim) + "D");
}

constexpr int DIM = PY_WRAPPER_DIM;

const std::string CoorTypeStr = get_type_str("CoorType", DIM);
const std::string CordListStr = get_type_str("CordList", DIM);
const std::string GridBasePtrStr = get_type_str("GridBasePtr", DIM);
const std::string GridVectorPtr = get_type_str("GridVectorPtr", DIM);
const std::string PlayGroundStr = get_type_str("PlayGround", DIM);

BOOST_PYTHON_MODULE(LIB_NAME) {
    class_<typename Grid<DIM>::CoorType>("CoorType")
        .def("size", &Grid<DIM>::CoorType::size)
        .def("__len__", &Grid<DIM>::CoorType::size)
        .def("get", coor_get<DIM>)
        .def("set", coor_set<DIM>);

    class_<std::vector<typename Grid<DIM>::CoorType>>("CordList")
        .def((vector_indexing_suite<std::vector<Grid<DIM>::CoorType>>()));

    class_<Grid<DIM>, std::shared_ptr<Grid<DIM>>, boost::noncopyable>(
        "GridBasePtr", no_init);

    class_<VectorGrid<DIM>, bases<Grid<DIM>>, std::shared_ptr<VectorGrid<DIM>>>(
        "GridVectorPtr", init<Grid<DIM>::CoorType>())
        .def("sum", &GridImplPt<VectorGrid<DIM>>::sum)
        .def("get_digest", &GridImplPt<VectorGrid<DIM>>::get_digest)
        .def("get_live_cells", &GridImplPt<VectorGrid<DIM>>::get_live_cells,
             boost::python::return_value_policy<
                 boost::python::return_by_value>())
        .def("set_cell", &GridImplPt<VectorGrid<DIM>>::set_cell)
        .def("evolve", &GridImplPt<VectorGrid<DIM>>::evolve);

    class_<PlayGround<DIM>>("PlayGround", init<Grid<DIM>::CoorType>())
        .def("set_up", &PlayGround<DIM>::set_up)
        .def("getGrid", &PlayGround<DIM>::getGrid)
        .def("run", &PlayGround<DIM>::run, playground_run_overload());
}
