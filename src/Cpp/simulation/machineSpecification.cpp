#include "machineSpecification.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <array>
#include <vector>
using json = nlohmann::json;

MachineSpecification::MachineSpecification(std::string filepath)
{
	std::ifstream file(filepath);
	json data = json::parse(file);
	//int N = data["size"];
	name = data["name"];
	json rotors = data["rotors"];
	int j = 0;
	for (json rotor : rotors) {
		std::string wires = rotor["wirings"];
		std::vector<std::string> turns = rotor["turnovers"];
		std::array<int, 26> wiring = sequential;
		for (int i = 0; i < wires.size(); i++) {
			wiring[i] = (int)wires[i]-64;
		}
		std::array<int,2> turnovers;
		for (int i = 0; i < turns.size(); i++) {
			turnovers[i] = (int)turns[i][0] - 64;
		}
		RotorSpecification rot(j,wiring,turnovers);
		j++;
		possibleRotors.push_back(rot);
	}
	json reflectors = data["reflectors"];
	int k = 0;
	for (std::string reflector : reflectors) {
		std::array<int, 26> wiring = sequential;
		for (int i = 0; i < reflector.size(); i++) {
			wiring[i] = (int) reflector[i] - 64;
		}
		k++;
		Reflector reflectr(j, wiring);
		possibleReflectors.push_back(reflectr);
	}
	
}

RotorSpecification& MachineSpecification::getNext()
{
	index++;
	if (index >= possibleRotors.size()) {
		index = 0;
	}
	return possibleRotors[index];
}

Reflector& MachineSpecification::getNextReflector()
{
	reflectorIndex++;
	if (reflectorIndex >= possibleRotors.size()) {
		reflectorIndex = 0;
	}
	return possibleReflectors[reflectorIndex];
}
