#include <pybind11/pybind11.h>
#include "funcs.h"
namespace py  = pybind11;

PYBIND11_MODULE(binds, m){
    py::class_<funcs::item>(m,"item").def("__init__",&funcs::item::item)
}