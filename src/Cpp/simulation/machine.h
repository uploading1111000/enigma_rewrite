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
class Machine { //central class that handles most functions of the program
private:
	MachineSpecification* specification = nullptr;
protected:
	std::array<Rotor, 3> rotors; //stores array of rotors with length 3, 4th rotor is stored in the machine4 on its own
	Reflector reflector;
	Plugboard plugboard;
	virtual std::array<int, 26> getFourth() { return sequential; }; //intended to be overriden for the 4th rotor
public:
	Machine(MachineSpecification& spec, std::array<int, 3> rotorIds = {}, int reflector = 1, std::vector<std::array<char, 2>> plugboard = {});
	Machine() {}; //don't call this
	void setPositions(std::array<int, 3>); //a variety of setters. a plural implies it takes an array and updates the entire machine
	void setPosition(int N, int position); //singular takes an index and updates that 1 rotor
	void setRings(std::array<int, 3>);
	void setRing(int N, int ring);
	void setRotor(Place, int id);
	void setRotor(int, int id);
	void setRotors(std::array<int,3>);
	void incrementRotor(int N);  //takes the id of the current rotor and increments/decrements, then wraps around
	void decrementRotor(int N);
	void incrementPosition(int N); //just takes the position and ring
	void decrementPosition(int N);
	void incrementRing(int N);
	void decrementRing(int N);
	void setPlugboard(std::vector<std::array<char, 2>> letterpairs); //re-initialises the plugboard. not sure what happens to old plugboard
	int getPosition(int N) { return rotors[N].getPosition(); };
	std::array<int, 3> getPositions() { return { rotors[0].getPosition(),rotors[1].getPosition(),rotors[2].getPosition() }; };
	int getRing(int N) { return rotors[N].getRingPosition(); };
	std::array<int, 3> getRings() {
		std::array<int, 3> returnable;
		for (int i = 0; i < 3; i++) {
			returnable[i] = rotors[i].getRingPosition();
		}
		return returnable;
	}
	std::vector<int> getTurnpoints(int N);
	std::string getRotorID(int N) { return rotors[N].getRotorID(); };
	std::array<std::string,3> getRotorIDs(){
		std::array<std::string,3> returnable;
		for (int i = 0; i < 3; i++) {
			returnable[i] = rotors[i].getRotorID();
		}
		return returnable;
	}
	Rotor* getRotor(int N) { return &rotors[N]; }
	Reflector* getReflector() { return &reflector; };
	Plugboard* getPlugboard() { return &plugboard; };
	std::array<int, 26> getWiring(int N); //handles 0 = reflector, 1 = rotor4, 2-3 = rotors, 4 = plugboard
	virtual MachineSpecification* getSpecification() { return specification; };
	void mutateRotors(); //mutates rotors, following double stepping and turnover rules
	virtual int encryptLetter(int); //most important method in the program, encrypts a letter fully
	char encryptLetter(char); //chars, strings and vector methods are just wrappers for the int methods
	std::vector<int> encryptWord(std::vector<int>);
	std::string encryptWord(std::string);
	virtual std::vector<int> encryptLetterVerbose(int); //visualiser encrypt
	std::string encryptLetterVerbose(char);
};