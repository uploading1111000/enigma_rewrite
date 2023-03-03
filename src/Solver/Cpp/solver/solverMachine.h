#include "../analysis/analysisAbstract.h"
#include "../utils/utils.h"
#include "machine.h"
#include <optional>
class SolverMachine : public Machine {
protected:
	std::array<Rotor, 3> initialPositions;
	Analyser* analyser;
	std::vector<int> ciphertext;
public:
	SolverMachine(MachineSpecification&, std::optional<std::array<int, 3>> rotorIndexes, std::optional<int> reflector,
		std::optional<std::vector<std::array<char, 2>>> plugPairs, std::string ciphertext, Analyser*);
	std::pair<std::array<int, 3>, float> findBestPositions();
	void findBestRotors();
	void findBestRings();
	void findBestPlugs();

};