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
	py::class_<Machine>(m, "Machine")
		.def(py::init<MachineSpecification&, std::array<int, 3>, int, std::vector<std::array<char, 2>>>(),py::arg("spec"),
			py::arg("rotorIds") = std::array<int, 3>{0, 1, 2}, py::arg("reflector") = 1, py::arg("plugboard") = std::vector<std::array<int, 3>>{})
		.def("encryptWord", static_cast<std::string(Machine::*)(std::string)>(&Machine::encryptWord))
		.def("setPositions", &Machine::setPositions)
		.def("setPosition", &Machine::setPosition)
		.def("setRingS", &Machine::setRings)
		.def("setRing", &Machine::setRing)
		.def("setRotors", &Machine::setRotors)
		.def("setRotor", static_cast<void (Machine::*)(int, int)>(&Machine::setRotor));
	py::class_<MachineFour, Machine>(m, "MachineFour")
		.def(py::init<MachineSpecificationFour&, std::array<int, 3>, int,int, std::vector<std::array<char, 2>>>(), py::arg("spec"),
			py::arg("rotorIds") = std::array<int, 3>{0, 1, 2}, py::arg("rotor4Id") = 0, py::arg("reflector") = 1, py::arg("plugboard") = std::vector<std::array<int, 3>>{});

}