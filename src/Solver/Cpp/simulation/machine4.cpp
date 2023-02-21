#include "machine4.h"

MachineFour::MachineFour(MachineSpecificationFour& spec, std::array<int, 3> rotorIds,int rotor4Id, int reflectorId, std::vector<std::array<char, 2>> plugboardPairs):
	Machine::Machine(MachineSpecification(spec),rotorIds,reflectorId,plugboardPairs)
{
	specification = std::unique_ptr<MachineSpecificationFour>(new MachineSpecificationFour(spec));
	for (int i = 0; i < 3; i++) {
		rotors[i] = Rotor(specification->getRotor(rotorIds[i]));
	}
	reflector = specification->getReflector(reflectorId);
	plugboard = Plugboard(plugboardPairs);
	rotor4 = Rotor(specification->getRotorFour(rotor4Id));
}
