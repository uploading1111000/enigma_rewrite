#include "../analysis/analysisAbstract.h"
#include "../utils/utils.h"
#include "machine4.h"
#include "solverMachine.h"
#include <optional>

#define quadruple std::array<int,4>

struct maxPosition4 {
	quadruple pos;
	float score;
};

struct maxSetting4 {
	quadruple pos;
	quadruple rotors;
	float score;
};

class SolverMachineFour : public MachineFour, public SolverMachine {
public:
	SolverMachineFour(MachineSpecificationFour&, std::optional<std::array<int, 3>> rotorIndexes, std::optional<int> rotor4, std::optional<int> reflector,
		std::optional<std::vector<std::array<char, 2>>> plugPairs, std::string ciphertext, Analyser*);
	float findBestRotors();
	float findBestRotorsWith4();
};