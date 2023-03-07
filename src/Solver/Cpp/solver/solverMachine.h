#include "../analysis/analysisAbstract.h"
#include "../utils/utils.h"
#include "machine.h"
#include <optional>
#pragma once

#define triple std::array<int,3>
#define double std::array<int,2>

struct maxPosition {
	triple pos;
	float score;
};

struct maxSetting {
	triple pos;
	triple rotors;
	float score;
};

struct maxRings {
	double rings;
	float score;
};

struct maxPlugs {
	Plugboard plug;
	float score;
	std::array<int,2> newPair;
};

class SolverMachine : virtual public Machine {
protected:
	std::array<int, 3> initialPositions;
	Analyser* analyser;
	std::vector<int> ciphertext;
	SolverMachine();
public:
	SolverMachine(MachineSpecification&, std::optional<std::array<int, 3>> rotorIndexes, std::optional<int> reflector,
		std::optional<std::vector<std::array<char, 2>>> plugPairs, std::string ciphertext, Analyser*);
	maxPosition findBestPositions();
	virtual float findBestRotors();
	float findBestRings();
	float findBestPlugs();
	void changeAnalyser(Analyser* analyserIn) { analyser = analyserIn; };

};