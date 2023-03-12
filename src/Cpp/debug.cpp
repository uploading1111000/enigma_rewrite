#include <iostream>
#include <set>
#include "NGram.h"
#include "utils.h"
#include "solverMachine4.h"
#include "indexOfCoincidenceOptimal.h"

std::string clean(std::string in) {
	std::string returnable;
	for (int letter : in) {
		if (letter > 64 and letter < 91) returnable.push_back((char)letter);
		else if (letter > 96 and letter < 123) returnable.push_back((char)letter - 32);
	}
	return returnable;
}

int main(){
	TriGram tri("../../../ngramData/gramstri.bin");
	IndexOfCoincidenceOptimised IOCO;
	MachineSpecification spec("../../../simulation/machineJsons/EnigmaM3.json");
	std::string start;
	std::getline(std::cin, start);
	start = clean(start);
	std::cout << start.size() << "\n";
	SolverMachine solver(spec, std::optional<std::array<int, 3>> {}, std::optional<int> {1}, std::optional<std::vector<std::array<char, 2>>>{}, start, & IOCO);
	solver.findBestRotors();
	std::cout << "rotors found\n";
	for (int i = 0; i < 3; i++) {
		std::cout << solver.getRotor(i)->getRotorID() << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << solver.getRotor(i)->getPosition() << " ";
	}
	std::cout << std::endl;
	std::cout << solver.encryptWord(start) << std::endl;
	solver.changeAnalyser(&tri);
	solver.findBestRings();
	std::cout << "rings found\n";
	for (int i = 0; i < 3; i++) {
		std::cout << solver.getRotor(i)->getRotorID() << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << solver.getRotor(i)->getRingPosition() << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << solver.getRotor(i)->getPosition() << " ";
	}
	std::cout << std::endl;
	std::cout << solver.encryptWord(start) << std::endl;
	solver.findBestPlugs();
	std::cout << "plugs found\n";
	for (int i = 0; i < 3; i++) {
		std::cout << solver.getRotor(i)->getRotorID() << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << solver.getRotor(i)->getRingPosition() << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << solver.getRotor(i)->getPosition() << " ";
	}
	std::cout << std::endl;
	std::cout << solver.encryptWord(start);
}