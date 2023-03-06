#include "solverMachine4.h"

SolverMachineFour::SolverMachineFour(MachineSpecificationFour& spec, std::optional<std::array<int, 3>> rotorIndexes, std::optional<int> rotor4, std::optional<int> reflector, std::optional<std::vector<std::array<char, 2>>> plugPairs, std::string ciphertextStr, Analyser* analyserIn) :
	MachineFour(spec, rotorIndexes ? rotorIndexes.value() : {0, 1, 2}, rotor4 ? rotor4.value() : 0, reflector ? reflector.value() : 1, plugPairs ? plugPairs.value() : std::vector<std::array<char, 2>>{})
{
	analyser = analyserIn;
	ciphertext = vectorFromString(ciphertextStr);
}
