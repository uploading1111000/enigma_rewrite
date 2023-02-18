#include "machineSpecification.h"
#include <string>
#include "rotorSpecification.h"
#include <vector>
#pragma once

class MachineSpecificationFour : public MachineSpecification{
protected:
	std::vector<RotorSpecification> possibleRotorsFour;
	int fourIndex = -1;
public:
	int getN() {return 4;};
	MachineSpecificationFour(std::string filename);
	RotorSpecification getRotorFour(int N){
		return possibleRotorsFour[N];
	};
	RotorSpecification getNextFour();
	size_t getRotorFourSize(){ return possibleRotorsFour.size();};
};