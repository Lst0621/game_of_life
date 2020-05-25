#include <boost/python.hpp>
#include <boost/python/overloads.hpp>
#include "Playground.h"
using namespace boost::python;
using namespace lst::gol;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(playground_run_overload, PlayGround::run,
                                       0, 1)
BOOST_PYTHON_MODULE(gol_py) {
    class_<PlayGround>("PlayGround", init<int, int>())
        .def("set_up", &PlayGround::set_up)
        .def("run", &PlayGround::run, playground_run_overload());
}
