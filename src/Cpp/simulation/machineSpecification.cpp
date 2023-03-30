#include "machineSpecification.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <array>
#include <vector>
using json = nlohmann::json;

MachineSpecification::MachineSpecification(std::string filepath) //handles json load to get a machine specification
{
	std::ifstream file(filepath); //open file
	json data = json::parse(file); //parse into json object
	//int N = data["size"];
	name = data["name"]; //set name
	json rotors = data["rotors"]; //move rotors tag into new json object
	int j = 0;
	for (json rotor : rotors) { //iterate over json objects (each defining a rotor)
		std::string wires = rotor["wirings"]; //get wirings as string
		std::vector<std::string> turns = rotor["turnovers"]; //get turnovers as vectors of strings
		std::array<int, 26> wiring = sequential; 
		for (int i = 0; i < wires.size(); i++) {
			wiring[i] = (int)wires[i]-64; //turn wiring string into array
		}
		std::array<int,2> turnovers;
		for (int i = 0; i < turns.size(); i++) {
			turnovers[i] = (int)turns[i][0] - 64; //turn turnover string into array
		}
		RotorSpecification rot(j,wiring,turnovers); //create rotorspecification
		j++;
		possibleRotors.push_back(rot); //push rotorspecification to machinespec
	}
	json reflectors = data["reflectors"]; //move reflectors into json array
	int k = 0;
	for (std::string reflector : reflectors) { //iterate over reflector strings
		std::array<int, 26> wiring = sequential;
		for (int i = 0; i < reflector.size(); i++) {
			wiring[i] = (int) reflector[i] - 64; //convert wiring string to array
		}
		k++;
		Reflector reflectr(j, wiring);
		possibleReflectors.push_back(reflectr); //initialise and push back possible reflectors
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
