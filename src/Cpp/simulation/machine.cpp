#include "machine.h"
#include "machine.h"
#include "machine.h"
#include "machine.h"
#include "machine.h"
#include "machine.h"

inline int convert(char in) {
	return (int) in - 64;
}

inline char convert(int in) {
	return (char)in + 64;
}

Machine::Machine(MachineSpecification& spec, std::array<int, 3> rotorIds, int reflectorId, std::vector<std::array<char, 2>> plugboardPairs)
{
	specification = &spec;
	setRotors(rotorIds);
	reflector = specification->getReflector(reflectorId);
	plugboard = Plugboard(plugboardPairs);
}

void Machine::incrementRotor(int N) {
	int curr = rotors[N].getID();
	curr++;
	if (curr >= this->getSpecification()->getRotorLength()) {
		curr = 0;
	}
	setRotor(N, curr);
}
void Machine::decrementRotor(int N) {
	int curr = rotors[N].getID();
	curr--;
	if (curr < 0) {
		curr = this->getSpecification()->getRotorLength()-1;
	}
	setRotor(N, curr);
}

void Machine::setPositions(std::array<int, 3> positions)
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

void Machine::setRotor(Place place, int id)
{
	rotors[place] = Rotor(this->getSpecification()->getRotor(id), place);
}

void Machine::setRotor(int place, int id)
{
	switch (place) {
	case 0:
		rotors[place] = Rotor(this->getSpecification()->getRotor(id), left);
		break;
	case 1:
		rotors[place] = Rotor(this->getSpecification()->getRotor(id), middle);
		break;
	case 2:
		rotors[place] = Rotor(this->getSpecification()->getRotor(id), right);
		break;
	default:
		rotors[place] = Rotor(this->getSpecification()->getRotor(id), turnless);
		break;
	}
	
}

void Machine::setRotors(std::array<int,3> ids)
{
	for (int i = 0; i < 3; i++) {
		setRotor(i, ids[i]);
	}
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
	int out = start;
	if (start > 0 and start < 27) out = this->encryptLetter(start);
	else if (start > 32 and start < 59) out = this->encryptLetter(start - 32);
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
	returnable.push_back(leftF);
	//int fourthF = rotorFour.Transform(leftF)
	int reflected = reflector.Transform(leftF);
	returnable.push_back(reflected);
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
	std::vector<int> result = this->encryptLetterVerbose(start);
	std::string returnable;
	for (int num : result) {
		returnable.push_back(convert(num));
	}
	return returnable;
}

std::array<int, 26> Machine::getWiring(int N) {
	if (N == 0) {
		return sequential;
	}
	else if (N == 1) {
		return this->getFourth();
	}
	else if (N >= 2 && N <= 4) {
		std::array<int,26> normal = rotors[N - 2].getWiring();
		std::array<int, 26> returnable;
		for (int i = 1; i < 27; i++) {
			int indexA = i - rotors[N-2].getPosition() + rotors[N-2].getRingPosition();
			int indexB = normal[i-1] - rotors[N-2].getPosition() + rotors[N-2].getRingPosition();
			normalise(indexA);
			normalise(indexB);
			returnable[indexA - 1] = indexB;
		}
		return returnable;
	}
	else {
		return plugboard.getWiring();
	}
}

void Machine::incrementPosition(int N) {
	int prePos = rotors[N].getPosition() + 1;
	normalise(prePos);
	rotors[N].setPosition(prePos);
}

void Machine::decrementPosition(int N) {
	int prePos = rotors[N].getPosition() - 1;
	normalise(prePos);
	rotors[N].setPosition(prePos);
}

void Machine::incrementRing(int N) {
	int preRing = rotors[N].getRingPosition() + 1;
	normalise(preRing);
	rotors[N].setRing(preRing);
}

void Machine::decrementRing(int N) {
	int preRing = rotors[N].getRingPosition() - 1;
	normalise(preRing);
	rotors[N].setRing(preRing);
}

void Machine::setPlugboard(std::vector<std::array<char, 2>> letterpairs)
{
	plugboard = Plugboard(letterpairs);
}

std::vector<int> Machine::getTurnpoints(int N) {
	std::array<int, 2> raw = rotors[N].getTurnpoints();
	std::vector<int> returnable;
	for (int val : raw) {
		if (val != 0) {
			int real = val - rotors[N].getPosition();
			normalise(real);
			returnable.push_back(real);
		}
	}
	return returnable;
}