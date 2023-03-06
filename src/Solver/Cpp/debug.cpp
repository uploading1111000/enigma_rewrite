#include <iostream>
#include <set>
#include "NGram.h"
#include "utils.h"
#include "solverMachine.h"
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
	SolverMachine solver(spec, std::optional<std::array<int, 3>> {}, std::optional<int> {}, std::optional<std::vector<std::array<char, 2>>>{}, start, &IOCO);
	solver.findBestRotors();
	for (int i = 0; i < 3; i++) {
		std::cout << solver.getRotor(i)->getRotorID() << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << solver.getRotor(i)->getPosition() << " ";
	}
	std::cout << solver.encryptWord(start);

}