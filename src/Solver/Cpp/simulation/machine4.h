#include "machine.h"
#include "machineSpecification4.h"
class MachineFour : public Machine {
private:
	std::unique_ptr<MachineSpecificationFour> specification;
protected:
	Rotor rotor4;
public:
	MachineFour(MachineSpecificationFour&, std::array<int, 3>, int rotor4ID, int reflectorID, std::vector<std::array<char, 2>>);
	void setRotorFourPosition(int position) { rotor4.setPosition(position); };
	void setRotorFourRing(int ring) { rotor4.setRing(ring); };
	Rotor* getRotorFour() { return &rotor4; };
	int encryptLetter(int);
	using Machine::encryptLetter;
	using Machine::encryptWord;
	std::vector<int> encryptLetterVerbose(int);
	using Machine::encryptLetterVerbose;
};