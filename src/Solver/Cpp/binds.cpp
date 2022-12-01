#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "funcs.h"
namespace py  = pybind11;

PYBIND11_MODULE(binds, m){
    m.def("mergesort", &sorts::mergesort);
}