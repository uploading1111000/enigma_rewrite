#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "machineSpecification.h"
#include "machineSpecification4.h"
#include "machine.h"
#include "machine4.h"
#include "solverMachine.h"
#include "solverMachine4.h"
#include "NGram.h"
#include "indexOfCoincidence.h"
namespace py  = pybind11;

PYBIND11_MODULE(binds, m){
	py::class_<MachineSpecification>(m, "MachineSpecification")
		.def(py::init<std::string>())
		.def("getName", &MachineSpecification::getName)
		.def("getN", &MachineSpecification::getN);
	py::class_<MachineSpecificationFour, MachineSpecification>(m, "MachineSpecificationFour")
		.def(py::init <std::string>());
	py::class_<Machine> (m, "Machine")
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
	py::class_<MachineFour, Machine>(m, "MachineFour")
		.def(py::init<MachineSpecificationFour&, std::array<int, 3>, int, int, std::vector<std::array<char, 2>>>(), py::arg("spec"),
			py::arg("rotorIds") = std::array<int, 3>{0, 1, 2}, py::arg("rotor4Id") = 0, py::arg("reflector") = 1, py::arg("plugboard") = std::vector<std::array<int, 3>>{})
		.def("encryptWord", static_cast<std::string(MachineFour::*)(std::string)>(&MachineFour::encryptWord));
	py::class_<Analyser>(m, "AbstractAnalyser")
		.def("getName", &Analyser::getName);
	py::class_<IndexOfCoincidence, Analyser>(m, "IndexOfCoincidence")
		.def(py::init<>())
		.def("score",&IndexOfCoincidence::score);
	py::class_<BiGram, Analyser>(m, "BiGrams")
		.def(py::init<std::string>())
		.def("score", &BiGram::score);
	py::class_<TriGram, Analyser>(m, "TriGrams")
		.def(py::init<std::string>())
		.def("score", &TriGram::score);
	py::class_<QuadGram, Analyser>(m, "QuadGrams")
		.def(py::init<std::string>())
		.def("score", &QuadGram::score);
	py::class_<SolverMachine, Machine>(m, "SolverMachine")
		.def(py::init<MachineSpecification&, std::optional<std::array<int, 3>>, std::optional<int>,
			std::optional<std::vector<std::array<char, 2>>>, std::string, Analyser*>(), py::arg("spec"),
			py::arg("rotorIds") = std::optional<std::array<int, 3>>{}, py::arg("reflector") = std::optional<int>{},
			py::arg("plugboard") = std::optional<std::vector<std::array<char, 2>>>{}, py::arg("ciphertext"),py::arg("analyser") = new IndexOfCoincidence())
		.def("findRotors",&SolverMachine::findBestRotors);
}