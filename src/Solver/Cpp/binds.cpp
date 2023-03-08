#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "machineSpecification.h"
#include "machineSpecification4.h"
#include "machine.h"
#include "machine4.h"
#include "solverMachine.h"
#include "solverMachine4.h"
namespace py  = pybind11;

PYBIND11_MODULE(binds, m){
	py::class_<MachineSpecification>(m, "MachineSpecification")
		.def(py::init<std::string>())
		.def("getName", &MachineSpecification::getName)
		.def("getN", &MachineSpecification::getN);
	py::class_<MachineSpecificationFour, MachineSpecification>(m, "MachineSpecificationFour")
		.def(py::init <std::string>());
}