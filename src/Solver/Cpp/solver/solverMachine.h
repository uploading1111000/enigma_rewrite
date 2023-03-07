#include "../analysis/analysisAbstract.h"
#include "../utils/utils.h"
#include "machine.h"
#include <optional>
#pragma once

#define triple std::array<int,3>

struct maxPosition {
	triple pos;
	float score;
};

struct maxSetting {
	triple pos;
	triple rotors;
	float score;
};

class SolverMachine : public Machine {
protected:
	std::array<Rotor, 3> initialPositions;
	Analyser* analyser;
	std::vector<int> ciphertext;
	SolverMachine();
public:
	SolverMachine(MachineSpecification&, std::optional<std::array<int, 3>> rotorIndexes, std::optional<int> reflector,
		std::optional<std::vector<std::array<char, 2>>> plugPairs, std::string ciphertext, Analyser*);
	maxPosition findBestPositions();
	virtual float findBestRotors();
	void findBestRings();
	void findBestPlugs();
	

};