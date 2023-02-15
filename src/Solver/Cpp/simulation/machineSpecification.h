#include "rotorSpecification.h"
#include "reflector.h"
#include <vector>

class MachineSpecification{
protected:
	std::vector<RotorSpecification> possibleRotors;
	std::vector<Reflector> possibleReflectors;
	int index = 0;
public:
	int getN(){return 3;};
	RotorSpecification& getRotor(int N) {return possibleRotors[n];};
	RotorSpecification& getNext() {
		index += 1;
		if (index >= possibleRotors.size()){
			index = 0;
		}
		return possibleRotors[index];
	}
}