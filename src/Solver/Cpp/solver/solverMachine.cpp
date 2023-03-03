#include "solverMachine.h"

SolverMachine::SolverMachine(MachineSpecification& spec, std::optional<std::array<int,3>> rotorIndexes, std::optional<int> reflector, 
		std::optional<std::vector<std::array<char, 2>>> plugPairs, std::string ciphertextIn, Analyser* analyserIn):
		Machine::Machine(spec,rotorIndexes ? rotorIndexes.value() : std::array<int,3>{2, 1, 0}, reflector ? reflector.value() : 1, plugPairs ? plugPairs.value() : std::vector<std::array<char,2>>{}) {
	ciphertext = vectorFromString(ciphertextIn);
	analyser = analyserIn;
}

void SolverMachine::findBestRotors(){
	std::pair<std::pair<std::array<int, 3>, std::array<int, 3>>, float> max;
	int numberOfRotors = this->getSpecification()->getRotorLength();
	for (int l = 0; l < numberOfRotors; l++){
		rotors[left] = this->getSpecification()->getRotor(l);
		for (int m = 0; m < numberOfRotors; m++){
			if (m==l) continue;
			rotors[middle] = this->getSpecification()->getRotor(m);
			for (int r = 0; r < numberOfRotors; r++){
				if (r == l || r == m) continue;
				rotors[right] = this->getSpecification()->getRotor(r);
				std::pair<std::array<int,3>,float> best = findBestPositions();
				if (best.second > max.second){
						max = {{{l,m,r},best.first},best.second};
				}
			}
		}
	}
}

std::pair<std::array<int,3>, float> SolverMachine::findBestPositions(){
	std::pair<std::array<int,3>,float> max = {{1,1,1},0};
	for (int li = 1; li < 27; li++){
		rotors[left].setPosition(li);
		for (int mi = 1; mi < 27; mi++){
			rotors[middle].setPosition(mi);
			for(int ri = 1; ri < 27; ri++){
				rotors[right].setPosition(ri);
				std::vector<int> result = this->encryptWord(ciphertext);
				float score = analyser->score(result);
				if ( score > max.second){
					max = {{li,mi,ri},score};
				}
			}
		}
	}
	return max;
}