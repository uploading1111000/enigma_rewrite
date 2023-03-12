#include "machineSpecification.h"
#include "rotor.h"
#include "rotorSpecification.h"
#include "plugboard.h"
#include "reflector.h"
#include <memory>
#include <array>
#include <vector>
#include <iostream>
#pragma once
class Machine {
private:
	MachineSpecification* specification = nullptr;
protected:
	std::array<Rotor, 3> rotors;
	Reflector reflector;
	Plugboard plugboard;
public:
	Machine(MachineSpecification& spec, std::array<int, 3> rotorIds = {}, int reflector = 1, std::vector<std::array<char, 2>> plugboard = {});
	Machine() {}; //don't call this
	void setPositions(std::array<int, 3>);
	void setPosition(int N, int position);
	void setRings(std::array<int, 3>);
	void setRing(int N, int ring);
	void setRotor(Place, int id);
	void setRotor(int, int id);
	void setRotors(std::array<int,3>);
	Rotor* getRotor(int N) { return &rotors[N]; }
	Reflector* getReflector() { return &reflector; };
	Plugboard* getPlugboard() { return &plugboard; };
	virtual MachineSpecification* getSpecification() { return specification; };
	void mutateRotors();
	virtual int encryptLetter(int);
	char encryptLetter(char);
	std::vector<int> encryptWord(std::vector<int>);
	std::string encryptWord(std::string);
	virtual std::vector<int> encryptLetterVerbose(int);
	std::string encryptLetterVerbose(char);
};