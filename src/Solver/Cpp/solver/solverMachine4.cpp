#include "solverMachine4.h"
#include <iostream>

SolverMachineFour::SolverMachineFour(MachineSpecificationFour& spec, std::optional<std::array<int, 3>> rotorIndexes, std::optional<int> rotor4, std::optional<int> reflector, std::optional<std::vector<std::array<char, 2>>> plugPairs, std::string ciphertextStr, Analyser* analyserIn) :
	MachineFour(spec, rotorIndexes ? rotorIndexes.value() : std::array<int,3>{0, 1, 2}, rotor4 ? rotor4.value() : 0, reflector ? reflector.value() : 1, plugPairs ? plugPairs.value() : std::vector<std::array<char, 2>>{})
{
	analyser = analyserIn;
	ciphertext = vectorFromString(ciphertextStr);
}
void SolverMachineFour::findBestRotors() {
	maxSetting4 max{ {},{},0 };
	int numberOfRotors = this->getSpecification()->getRotorLength();
	int totalL = numberOfRotors * (numberOfRotors - 1) * (numberOfRotors - 2);
	int j = 0;
	for (int l = 0; l < numberOfRotors; l++) {
		rotors[left] = this->getSpecification()->getRotor(l);
		for (int m = 0; m < numberOfRotors; m++) {
			if (m == l) continue;
			rotors[middle] = this->getSpecification()->getRotor(m);
			for (int r = 0; r < numberOfRotors; r++) {
				if (r == l || r == m) continue;
				rotors[right] = this->getSpecification()->getRotor(r);
				for (int p = 1; p < 27; p++) {
					MachineFour::rotor4.setPosition(p);
					maxPosition best = findBestPositions();
					//std::cout << best.second << " " << rotors[left].getRotorID() << " " << rotors[middle].getRotorID() << " " << rotors[right].getRotorID() << "\n";
					std::cout << j++ << " / " << totalL << "\n";
					if (best.score > max.score) {
						//std::cout << best.first[0] << " " << best.first[1] << " " << best.first[2] << "\n";
						max = { {l,m,r},{best.pos[0],best.pos[1],best.pos[2],p},best.score};
					}
				}
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		rotors[i] = this->getSpecification()->getRotor(max.rotors[i]);
		rotors[i].setPosition(max.pos[i]);
		initialPositions[i] = max.pos[i];
	}
}