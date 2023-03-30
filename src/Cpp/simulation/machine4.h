#include "machine.h"
#include "machineSpecification4.h"
#pragma once
class MachineFour : virtual public Machine {
private:
	MachineSpecificationFour* specification; //hides the underlying MachineSpecification pointer, this means getSpecification must be used to access specification
protected:
	Rotor rotor4;
public:
	MachineFour(MachineSpecificationFour&, std::array<int, 3>, int rotor4ID, int reflectorID, std::vector<std::array<char, 2>>);
	void setRotorFourPosition(int position) { rotor4.setPosition(position); };
	void setRotorFourRing(int ring) { rotor4.setRing(ring); };
	void setRotorFour(int id);
	Rotor* getRotorFour() { return &rotor4; };
	MachineSpecificationFour* getSpecification() { return specification; };
	int encryptLetter(int);
	std::vector<int> encryptLetterVerbose(int);
	std::string encryptLetterVerbose(char);
	std::string encryptWord(std::string);
	char encryptLetter(char);
};