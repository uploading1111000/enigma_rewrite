#include "rotorSpecification.h"
#include "reflector.h"
#include <vector>
#include <string>
#pragma once

class MachineSpecification {
protected:
	std::vector<RotorSpecification>possibleRotors;
	std::vector<Reflector> possibleReflectors;
	int index = -1;
	int reflectorIndex = 0;
	std::string name = "Custom";
public:
	MachineSpecification(std::string filepath);
	virtual int getN() { return 3; };
	std::string getName() { return name; };
	RotorSpecification& getRotor(int N) { return possibleRotors[N]; };
	RotorSpecification& getNext();
	size_t getRotorLength() { return possibleRotors.size(); };
	Reflector& getReflector(int N) { return possibleReflectors[N]; };
	Reflector& getNextReflector();
	size_t getReflectorLength() { return possibleReflectors.size(); };
};