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

class SolverMachine : virtual public Machine {
protected:
	std::array<Rotor, 3> initialPositions;
	Analyser* analyser;
	std::vector<int> ciphertext;
public:
	SolverMachine(MachineSpecification&, std::optional<std::array<int, 3>> rotorIndexes, std::optional<int> reflector,
		std::optional<std::vector<std::array<char, 2>>> plugPairs, std::string ciphertext, Analyser*);
	SolverMachine();
	maxPosition findBestPositions();
	virtual void findBestRotors();
	void findBestRings();
	void findBestPlugs();
	

};