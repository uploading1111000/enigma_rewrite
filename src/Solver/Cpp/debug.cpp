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
	std::cout << tri.score(vectorFromString("QDDENIGMAHASANELECTROMECHARCJALROTORMECHANISMTHATSCRNGOLESTHELETTERSOFTHEALPHAEIBINTYPICALUSEONEPERSONENDZZSTEXTONTHEENIGMASKEYBOADPFNDANOTHERPERSONWRITESDOBLDJJMNBKOAGMZDJGQZPELGYTMGOVAMECZNTUNBTRCGKPOATHUISMNWGOMINJRKKMJMBFEUMFEIBNXAHFQUTWCHWUUVVSRCAUWWDUHCFQFUOSIBDIDSUZIQUIAQQBNALQHHKDMZIMYXGTGRTJCAZPCXOSROTTMCLKBODJHZRCBMHXTHBTSMUECDIBSGBZJXOHVOICTPOHPCLJWNZAYVNOSHXKJLGSTDPDNITQDSPYPRRZQELIGHTSWITHEACHKEYPRESL"));
	std::cout << "\n";
	std::cout << tri.score(vectorFromString(clean("The Enigma has an electromechanical rotor mechanism that scrambles the 26 letters of the alphabet. In typical use, one person enters text on the Enigma's keyboard and another person writes down which of the 26 lights above the keyboard illuminated at each key press. If plain text is entered, the illuminated letters are the ciphertext. Entering ciphertext transforms it back into readable plaintext. The rotor mechanism changes the electrical connections between the keys and the lights with each keypress.")));
	MachineSpecification spec("../../../simulation/machineJsons/EnigmaI.json");
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
	std::cout << solver.encryptWord(start);
	/*
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
	std::array<int,26> plugWires = solver.getPlugboard()->getWiring();
	for (int i = 1; i < 27; i++) {
		if (plugWires[i - 1] != i) {
			std::cout << i << plugWires[i - 1] << " ";
		}
	}
	std::cout << std::endl;
	std::cout << solver.encryptWord(start);*/
}