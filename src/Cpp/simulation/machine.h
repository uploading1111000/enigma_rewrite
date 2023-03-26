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
	virtual std::array<int, 26> getFourth() { return sequential; };
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
	void incrementRotor(int N);
	void decrementRotor(int N);
	void incrementPosition(int N);
	void decrementPosition(int N);
	void incrementRing(int N);
	void decrementRing(int N);
	void setPlugboard(std::vector<std::array<char, 2>> letterpairs);
	int getPosition(int N) { return rotors[N].getPosition(); };
	std::array<int, 3> getPositions() { return { rotors[0].getPosition(),rotors[1].getPosition(),rotors[2].getPosition() }; };
	int getRing(int N) { return rotors[N].getRingPosition(); };
	std::vector<int> getTurnpoints(int N);
	std::string getRotorID(int N) { return rotors[N].getRotorID(); };
	Rotor* getRotor(int N) { return &rotors[N]; }
	Reflector* getReflector() { return &reflector; };
	Plugboard* getPlugboard() { return &plugboard; };
	std::array<int, 26> getWiring(int N);
	virtual MachineSpecification* getSpecification() { return specification; };
	void mutateRotors();
	virtual int encryptLetter(int);
	char encryptLetter(char);
	std::vector<int> encryptWord(std::vector<int>);
	std::string encryptWord(std::string);
	virtual std::vector<int> encryptLetterVerbose(int);
	std::string encryptLetterVerbose(char);
};