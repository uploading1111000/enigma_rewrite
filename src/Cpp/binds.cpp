#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "machineSpecification.h"
#include "machineSpecification4.h"
#include "machine.h"
#include "machine4.h"
#include "solverMachine.h"
#include "solverMachine4.h"
namespace py  = pybind11;

class PyMachine : public Machine {
public:
	using Machine::Machine;
	int encryptLetter(int start) override { PYBIND11_OVERRIDE(int, Machine, encryptLetter, start); };
	std::vector<int> encryptLetterVerbose (int start) override { PYBIND11_OVERRIDE(std::vector<int>, Machine, encryptLetterVerbose, start); };
};

class PyMachineFour : public MachineFour {
public:
	using MachineFour::MachineFour;
	int encryptLetter(int start) override { PYBIND11_OVERRIDE(int, MachineFour, encryptLetter, start); };
	std::vector<int> encryptLetterVerbose(int start) override { PYBIND11_OVERRIDE(std::vector<int>, MachineFour, encryptLetterVerbose, start); };
};

PYBIND11_MODULE(binds, m){
	py::class_<MachineSpecification>(m, "MachineSpecification")
		.def(py::init<std::string>())
		.def("getName", &MachineSpecification::getName)
		.def("getN", &MachineSpecification::getN);
	py::class_<MachineSpecificationFour, MachineSpecification>(m, "MachineSpecificationFour")
		.def(py::init <std::string>());
	py::class_<Machine, PyMachine> (m, "Machine")
		.def(py::init<MachineSpecification&, std::array<int, 3>, int, std::vector<std::array<char, 2>>>(),py::arg("spec"),
			py::arg("rotorIds") = std::array<int, 3>{0, 1, 2}, py::arg("reflector") = 1, py::arg("plugboard") = std::vector<std::array<int, 3>>{})
		.def("encryptWord", static_cast<std::string(Machine::*)(std::string)>(&Machine::encryptWord))
		.def("encryptLetterVerbose", static_cast<std::string (Machine::*)(char)>(&Machine::encryptLetterVerbose))
		.def("encryptLetter", static_cast<int(Machine::*)(int)>(&Machine::encryptLetter))
		.def("setPositions", &Machine::setPositions)
		.def("setPosition", &Machine::setPosition)
		.def("setRingS", &Machine::setRings)
		.def("setRing", &Machine::setRing)
		.def("setRotors", &Machine::setRotors)
		.def("setRotor", static_cast<void (Machine::*)(int, int)>(&Machine::setRotor));
	py::class_<MachineFour, Machine, PyMachineFour>(m, "MachineFour")
		.def(py::init<MachineSpecificationFour&, std::array<int, 3>, int, int, std::vector<std::array<char, 2>>>(), py::arg("spec"),
			py::arg("rotorIds") = std::array<int, 3>{0, 1, 2}, py::arg("rotor4Id") = 0, py::arg("reflector") = 1, py::arg("plugboard") = std::vector<std::array<int, 3>>{})
		.def("encryptWord", static_cast<std::string(MachineFour::*)(std::string)>(&MachineFour::encryptWord));

}