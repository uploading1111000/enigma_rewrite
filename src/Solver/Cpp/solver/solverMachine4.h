#include "../analysis/analysisAbstract.h"
#include "../utils/utils.h"
#include "../simulation/machine4.h"
#include <optional>
class SolverMachineFour : public MachineFour {
protected:
	std::array<Rotor, 4> initialPositions;
	Analyser* analyser;
	std::vector<int> ciphertext;
public:
	SolverMachineFour(MachineSpecificationFour&, std::optional<std::array<int, 3>> rotorIndexes, std::optional<int> rotor4, std::optional<int> reflector,
		std::optional<std::vector<std::array<char, 2>>> plugPairs, std::string ciphertext, Analyser*);
	std::pair<std::array<int, 3>, float> findBestPositions();
	void findBestRotors();
	void findBestRings();
	void findBestPlugs();

};