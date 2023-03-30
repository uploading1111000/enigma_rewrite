#include "machineSpecification4.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <array>
using json = nlohmann::json;

MachineSpecificationFour::MachineSpecificationFour(std::string filename) : MachineSpecification::MachineSpecification(filename) {
	//first 3 rotors loaded by inherited constructor, then file re-opened and 4th rotor loaded
	std::ifstream file(filename); //open file
	json data = json::parse(file); //parse to json object
	json rotors4 = data["rotors4"]; //get 4th rotors into json object
	int j = 0;
	for (std::string rotor : rotors4) { //iterate over 4th rotors as wiring strings
		std::array<int, 26> wirings;
		for (int i = 0; i < rotor.size(); i++) { //string to int array
			wirings[i] = (int)rotor[i] - 64;
		}
		RotorSpecification rot(j, wirings, {-1,-1}); //create rotor specification
		possibleRotorsFour.push_back(rot);
		j++;
	}
};
RotorSpecification MachineSpecificationFour::getNextFour()
{
	fourIndex++;
	if (fourIndex >= possibleRotorsFour.size()) {
		fourIndex = 0;
	}
	return possibleRotorsFour[fourIndex];
};