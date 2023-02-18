#include "machineSpecification.h"
#include "rotor.h"
#include "rotorSpecification.h"
#include "plugboard.h"
#include "reflector.h"
#include <array>
#include <vector>
class Machine {
protected:
	std::array<Rotor, 3> rotors;
	Reflector reflector;
	Plugboard plugboard;
	MachineSpecification* specification;

public:
	Machine(MachineSpecification&, std::array<int,3>, int, std::vector<std::array<char, 2>>);
	void setPositions(const std::array<int, 3>&);
	void setPosition(int N, int position);
	void setRings(std::array<int, 3>);
	void setRing(int N, int ring);
	Rotor* getRotor(int N) { return &rotors[N]; }
	Reflector* getReflector() { return &reflector; };
	Plugboard* getPlugboard() { return &plugboard; };
	MachineSpecification* getSpecification() { return specification; };
	void mutateRotors();
	virtual int encryptLetter(int);
	char encryptLetter(char);
	std::vector<int> encryptWord(std::vector<int>);
	std::string encryptWord(std::string);
	virtual std::vector<int> encryptLetterVerbose(int);
	std::string encryptLetterVerbose(char);
};