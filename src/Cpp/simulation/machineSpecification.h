#include "rotorSpecification.h"
#include "reflector.h"
#include <vector>
#include <string>
#pragma once

class MachineSpecification {
protected:
	std::vector<RotorSpecification>possibleRotors; 
	std::vector<Reflector> possibleReflectors; //possible rotord
	int index = -1; 
	int reflectorIndex = 0;
	std::string name = "Custom"; //name shown in menu dropdown
public:
	MachineSpecification(std::string filepath);
	virtual int getN() { return 3; };
	std::string getName() { return name; };
	RotorSpecification& getRotor(int N) { return possibleRotors[N]; };
	RotorSpecification& getNext(); //at a point during development, reflectors and rotors were going to be accessed sequentially
	size_t getRotorLength() { return possibleRotors.size(); };
	Reflector& getReflector(int N) { return possibleReflectors[N]; };
	Reflector& getNextReflector();
	size_t getReflectorLength() { return possibleReflectors.size(); };
	std::vector<std::string> getRotorIDs() { //dropdown menu
		std::vector<std::string> ids;
		for (auto r : possibleRotors) {
			ids.push_back(r.getRotorID());
		}
		return ids;
	}
};