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

struct maxSetting { //rotor position and rotor ids stored so can be accessed easier
	triple rotors;
	triple pos;
	float score;
};

struct maxRings {
	double rings;
	float score;
};

struct maxPlugs {
	Plugboard plug; //stores a full copy of plugboard, simpler to access later
	float score;
	std::array<int,2> newPair; //also the current best new pair of plugs
};

class SolverMachine : public Machine {
protected:
	std::array<int, 3> initialPositions;
	Analyser* analyser;
	std::vector<int> ciphertext;
	SolverMachine();
public:
	SolverMachine(MachineSpecification&, std::optional<std::array<int, 3>> rotorIndexes, std::optional<int> reflector,
		std::optional<std::vector<std::array<char, 2>>> plugPairs, std::string ciphertext, Analyser*);
	maxPosition findBestPositions(); //returns max position so the max rotor can automatically return to the best positions
	virtual float findBestRotors(); //virtual so can be overridden by solver4
	float findBestRings();
	float findBestPlugs();
	void changeAnalyser(Analyser* analyserIn) { analyser = analyserIn; }; //self explanatory
	void setPosition(int N, int pos);
	void setPositions(std::array<int, 3>);
	void homePosition();
	void changeCiphertext(std::string in) {ciphertext = vectorFromString(in);}; //self explanatory
};