#include <pybind11/pybind11.h>
#include "funcs.h"
namespace py  = pybind11;

PYBIND11_MODULE(binds, m){
    py::class_<item>(m, "item")
        .def(py::init<int, int>())
        .def("calc",&item::calc);
}