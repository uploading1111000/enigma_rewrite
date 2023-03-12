#include "machine4.h"

MachineFour::MachineFour(MachineSpecificationFour& spec, std::array<int, 3> rotorIds,int rotor4Id, int reflectorId, std::vector<std::array<char, 2>> plugboardPairs)
{
	specification = &spec;
	for (int i = 0; i < 3; i++) {
		rotors[i] = Rotor(specification->getRotor(rotorIds[i]));
	}
	reflector = specification->getReflector(reflectorId);
	plugboard = Plugboard(plugboardPairs);
	rotor4 = Rotor(specification->getRotorFour(rotor4Id));
}

void MachineFour::setRotorFour(int id)
{
	rotor4 = Rotor(this->getSpecification()->getRotorFour(id));
}

int MachineFour::encryptLetter(int start)
{
	std::cout << "hello\n";
	mutateRotors();
	int plugF = plugboard.Transform(start);

	int rightF = rotors[right].Transform(plugF);

	int middleF = rotors[middle].Transform(rightF);

	int leftF = rotors[left].Transform(middleF);

	int fourthF = rotor4.Transform(leftF);

	int reflected = reflector.Transform(fourthF);

	int fourthR = rotor4.TransformReverse(reflected);

	int leftR = rotors[left].TransformReverse(fourthR);

	int middleR = rotors[middle].TransformReverse(leftR);

	int rightR = rotors[right].TransformReverse(middleR);

	return plugboard.TransformReverse(rightR);
}

std::vector<int> MachineFour::encryptLetterVerbose(int start)
{
	std::vector<int> returnable;
	returnable.push_back(start);

	mutateRotors();

	int plugF = plugboard.Transform(start);
	returnable.push_back(plugF);

	int rightF = rotors[right].Transform(plugF);
	returnable.push_back(rightF);

	int middleF = rotors[middle].Transform(rightF);
	returnable.push_back(middleF);

	int leftF = rotors[left].Transform(middleF);
	returnable.push_back(leftF);

	int fourthF = rotor4.Transform(leftF);
	returnable.push_back(fourthF);

	int reflected = reflector.Transform(fourthF);
	returnable.push_back(reflected);

	int fourthR = rotor4.TransformReverse(reflected);
	returnable.push_back(fourthR);

	int leftR = rotors[left].TransformReverse(fourthR);
	returnable.push_back(leftR);

	int middleR = rotors[middle].TransformReverse(leftR);
	returnable.push_back(middleR);

	int rightR = rotors[right].TransformReverse(middleR);
	returnable.push_back(rightR);

	int plugR = plugboard.TransformReverse(rightR);
	returnable.push_back(plugR);
	return returnable;
}
