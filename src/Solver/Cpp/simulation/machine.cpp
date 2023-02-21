#include "machine.h"
#include <iostream>

inline int convert(char in) {
	return (int) in - 64;
}

inline char convert(int in) {
	return (char)in + 64;
}

Machine::Machine(MachineSpecification& spec, std::array<int, 3> rotorIds, int reflectorId, std::vector<std::array<char, 2>> plugboardPairs)
{
	specification = std::unique_ptr<MachineSpecification>(new MachineSpecification(spec));
	for (int i = 0; i < 3; i++) {
		rotors[i] = Rotor(specification->getRotor(rotorIds[i]));
	}
	reflector = specification->getReflector(reflectorId);
	plugboard = Plugboard(plugboardPairs);
}

void Machine::setPositions(const std::array<int, 3> &positions)
{
	for (int i = 0; i < 3; i++) {
		setPosition(i, positions[i]);
	}
}

void Machine::setPosition(int N, int position)
{
	rotors[N].setPosition(position);
}

void Machine::setRings(std::array<int, 3> rings)
{
	for (int i = 0; i < 3; i++) {
		setRing(i, rings[i]);
	}
}

void Machine::setRing(int N, int ring)
{
	rotors[N].setRing(ring);
}

void Machine::mutateRotors()
{
	rotors[left].mutate(
		rotors[middle].mutate(
			rotors[right].mutate(true)
		)
	);
}

int Machine::encryptLetter(int start)
{
	mutateRotors();
	int plugF = plugboard.Transform(start);
	int rightF = rotors[right].Transform(plugF);
	int middleF = rotors[middle].Transform(rightF);
	int leftF = rotors[left].Transform(middleF);
	//int fourthF = rotorFour.Transform(leftF)
	int reflected = reflector.Transform(leftF);
	//int fourthR = rotorFour.TransformReverse(reflected)
	int leftR = rotors[left].TransformReverse(reflected);
	int middleR = rotors[middle].TransformReverse(leftR);
	int rightR = rotors[right].TransformReverse(middleR);
	return plugboard.TransformReverse(rightR);
}

char Machine::encryptLetter(char letter)
{
	int start = convert(letter);
	int out = this->encryptLetter(start);
	return convert(out);
}

std::vector<int> Machine::encryptWord(std::vector<int> input)
{
	std::vector<int> returnable;
	for (int start : input) {
		int out = this->encryptLetter(start);
		returnable.push_back(out);
	}
	return returnable;
}

std::string Machine::encryptWord(std::string word)
{
	std::string returnable;
	for (char letter : word) {
		returnable.push_back(encryptLetter(letter));
	}
	return returnable;
}

std::vector<int> Machine::encryptLetterVerbose(int start)
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
	//int fourthF = rotorFour.Transform(leftF)
	int reflected = reflector.Transform(leftF);
	returnable.push_back(reflected);
	//int fourthR = rotorFour.TransformReverse(reflected)
	int leftR = rotors[left].TransformReverse(reflected);
	returnable.push_back(leftR);
	int middleR = rotors[middle].TransformReverse(leftR);
	returnable.push_back(middleR);
	int rightR = rotors[right].TransformReverse(middleR);
	returnable.push_back(rightR);
	int plugR = plugboard.TransformReverse(rightR);
	returnable.push_back(plugR);
	return returnable;
}

std::string Machine::encryptLetterVerbose(char letter)
{
	int start = convert(letter);
	std::vector<int> result = encryptLetterVerbose(start);
	std::string returnable;
	for (int num : result) {
		returnable.push_back(convert(num));
	}
	return returnable;
}
