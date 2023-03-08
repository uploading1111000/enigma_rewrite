#include "solverMachine.h"
#include "solverMachine.h"
#include "solverMachine.h"
#include "solverMachine.h"
#include "solverMachine.h"
#include <iostream>


SolverMachine::SolverMachine(MachineSpecification& spec, std::optional<std::array<int,3>> rotorIndexes, std::optional<int> reflector, 
		std::optional<std::vector<std::array<char, 2>>> plugPairs, std::string ciphertextIn, Analyser* analyserIn):
		Machine::Machine(spec,rotorIndexes ? rotorIndexes.value() : std::array<int,3>{2, 1, 0}, reflector ? reflector.value() : 0, plugPairs ? plugPairs.value() : std::vector<std::array<char,2>>{}) {
	ciphertext = vectorFromString(ciphertextIn);
	analyser = analyserIn;
	for (int i = 0; i < 3; i++) {
		if (rotorIndexes) setRotor(i, rotorIndexes.value()[i]);
	}
}

SolverMachine::SolverMachine()
{
}

float SolverMachine::findBestRotors(){
	maxSetting max{ {},{},0 };
	int numberOfRotors = this->getSpecification()->getRotorLength();
	int totalL = numberOfRotors * (numberOfRotors - 1) * (numberOfRotors - 2);
	int j = 0;
	for (int l = 0; l < numberOfRotors; l++){
		setRotor(left, l);
		for (int m = 0; m < numberOfRotors; m++){
			if (m==l) continue;
			setRotor(middle, m);
			for (int r = 0; r < numberOfRotors; r++){
				if (r == l || r == m) continue;
				setRotor(right, r);
				maxPosition best = findBestPositions();
				std::cout << best.score << " " << rotors[left].getRotorID() << " " << rotors[middle].getRotorID() << " " << rotors[right].getRotorID() << "\n";
				std::cout << j++ << " / " << totalL << "\n";
				if (best.score > max.score){
					//std::cout << best.first[0] << " " << best.first[1] << " " << best.first[2] << "\n";
					max = {{l,m,r},best.pos,best.score};
				}
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		setRotor(i, max.rotors[i]);
		rotors[i].setPosition(max.pos[i]);
		initialPositions[i] = max.pos[i];
	}
	return max.score;
}

float SolverMachine::findBestRings()
{
	maxRings max = { {},0 };
	for (int r = 1; r < 27; r++) {
		for (int m = 1; m < 27; m++) {
			rotors[right].setRing(r);
			int rpos = initialPositions[right] + r - 1;
			normalise(rpos);
			rotors[right].setPosition(rpos);
			rotors[middle].setRing(m);
			int mpos = initialPositions[middle] + m - 1;
			normalise(mpos);
			rotors[middle].setPosition(mpos);
			rotors[left].setPosition(initialPositions[left]);
			std::vector<int> result = this->encryptWord(ciphertext);
			float score = analyser->score(result);
			if (score > max.score) {
				max = { {r,m},score };
			}
		}
	}
	rotors[right].setRing(max.rings[0]);
	rotors[middle].setRing(max.rings[1]);
	initialPositions[right] = initialPositions[right] + max.rings[0] - 1;
	normalise(initialPositions[right]);
	initialPositions[middle] = initialPositions[middle] + max.rings[1] - 1;
	normalise(initialPositions[middle]);
	for (int i = 0; i < 3; i++) {
		rotors[i].setPosition(initialPositions[i]);
	}
	return max.score;
}

float SolverMachine::findBestPlugs()
{
	maxPlugs max{ plugboard,0 ,{} };
	std::set<int> used;
	for (int i = 0; i < 26; i++) {
		if (plugboard.getWiring()[i] != i + 1) {
			used.insert(i + 1);
		}
	}
	for (int i = 0; i < 13; i++) {
		bool changed = false;
		for (int a = 1; a < 27; a++) {
			if (used.contains(a)) continue;
			for (int b = 1; b < a; b++) {
				if (used.contains(b)) continue;
				plugboard.addPlug({ a,b });
				for (int j = 0; j < 3; j++) {
					rotors[j].setPosition(initialPositions[j]);
				}
				std::vector<int> result = this->encryptWord(ciphertext);
				float score = analyser->score(result);
				if (score > max.score) {
					changed = true;
					max = { plugboard,score,{a,b} };
				}
				plugboard.removeLast();
			}
		}
		plugboard = max.plug;
		used.insert(max.newPair[0]);
		used.insert(max.newPair[1]);
		if (!changed) break;
	}
	return max.score;
}

void SolverMachine::setPosition(int N, int pos)
{
	rotors[N].setPosition(pos);
	initialPositions[N] = pos;
}

maxPosition SolverMachine::findBestPositions(){
	maxPosition max = {{1,1,1},0};
	for (int li = 1; li < 27; li++){
		for (int mi = 1; mi < 27; mi++){
			for(int ri = 1; ri < 27; ri++){
				rotors[left].setPosition(li);
				rotors[middle].setPosition(mi);
				rotors[right].setPosition(ri);
				std::vector<int> result = this->encryptWord(ciphertext);
				float score = analyser->score(result);
				if ( score > max.score){
					max = {{li,mi,ri},score};
				}
			}
		}
	}
	return max;
}