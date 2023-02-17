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
	RotorSpecification getNextFour(){
		fourIndex++;
		if (fourIndex >= possibleRotorsFour.size()){
			fourIndex = 0;
		}
		return possibleRotorsFour[fourIndex];
	};
	size_t getRotorFourSize(){ return possibleRotorsFour.size();};
};