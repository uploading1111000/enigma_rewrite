#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "machineSpecification.h"
#include "machine.h"
#include "solverMachine.h"
#include "NGram.h"
#include "indexOfCoincidence.h"
namespace py  = pybind11;

PYBIND11_MODULE(binds, m){
	py::class_<MachineSpecification>(m, "MachineSpecification")
		.def(py::init<std::string>())
		.def("getName", &MachineSpecification::getName)
		.def("getN", &MachineSpecification::getN)
		.def("getRotorIDs",&MachineSpecification::getRotorIDs);
	py::class_<Machine>(m, "Machine")
		.def(py::init<MachineSpecification&, std::array<int, 3>, int, std::vector<std::array<char, 2>>>(), py::arg("spec"),
			py::arg("rotorIds") = std::array<int, 3>{0, 1, 2}, py::arg("reflector") = 1, py::arg("plugboard") = std::vector<std::array<int, 3>>{})
		.def("encryptWord", static_cast<std::string(Machine::*)(std::string)>(&Machine::encryptWord))
		.def("encryptLetterVerbose", static_cast<std::string(Machine::*)(char)>(&Machine::encryptLetterVerbose))
		.def("encryptLetter", static_cast<int(Machine::*)(int)>(&Machine::encryptLetter))
		.def("setPositions", &Machine::setPositions)
		.def("setPosition", &Machine::setPosition)
		.def("setRings", &Machine::setRings)
		.def("setRing", &Machine::setRing)
		.def("setRotors", &Machine::setRotors)
		.def("setRotor", static_cast<void (Machine::*)(int, int)>(&Machine::setRotor))
		.def("setPlugboard",&Machine::setPlugboard)
		.def("getWiring", &Machine::getWiring)
		.def("incrementRotor", &Machine::incrementRotor)
		.def("decrementRotor", &Machine::decrementRotor)
		.def("incrementPosition", &Machine::incrementPosition)
		.def("decrementPosition", &Machine::decrementPosition)
		.def("incrementRing", &Machine::incrementRing)
		.def("decrementRing", &Machine::decrementRing)
		.def("getRotorID", &Machine::getRotorID)
		.def("getPosition", &Machine::getPosition)
		.def("getPositions",&Machine::getPositions)
		.def("getRing",&Machine::getRing)
		.def("getTurnpoints",&Machine::getTurnpoints);
	py::class_<Analyser>(m, "AbstractAnalyser")
		.def("getName", &Analyser::getName);
	py::class_<IndexOfCoincidence, Analyser>(m, "IndexOfCoincidence")
		.def(py::init<>())
		.def("score",&IndexOfCoincidence::score);
	py::class_<BiGram, Analyser>(m, "BiGram")
		.def(py::init<std::string>())
		.def("score", &BiGram::score);
	py::class_<TriGram, Analyser>(m, "TriGram")
		.def(py::init<std::string>())
		.def("score", &TriGram::score);
	py::class_<QuadGram, Analyser>(m, "QuadGram")
		.def(py::init<std::string>())
		.def("score", &QuadGram::score);
	py::class_<SolverMachine, Machine>(m, "SolverMachine")
		.def(py::init<MachineSpecification&, std::optional<std::array<int, 3>>, std::optional<int>,
			std::optional<std::vector<std::array<char, 2>>>, std::string, Analyser*>(), py::arg("spec"),
			py::arg("rotorIds") = std::optional<std::array<int, 3>>{}, py::arg("reflector") = std::optional<int>{},
			py::arg("plugboard") = std::optional<std::vector<std::array<char, 2>>>{}, py::arg("ciphertext") = "", py::arg("analyser") = new IndexOfCoincidence())
		.def("setAnalyzer", &SolverMachine::changeAnalyser)
		.def("findRotors", &SolverMachine::findBestRotors)
		.def("findRings", &SolverMachine::findBestRings)
		.def("findPlugs", &SolverMachine::findBestPlugs)
		.def("changeCiphertext",&SolverMachine::changeCiphertext);
}