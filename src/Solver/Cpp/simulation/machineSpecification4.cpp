#include "machineSpecification4.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <array>
using json = nlohmann::json;

MachineSpecificationFour::MachineSpecificationFour(std::string filename) : MachineSpecification::MachineSpecification(filename){
	std::ifstream file(filename);
	json data = json::parse(file);
	json rotors4 = data["rotors4"];
	int j = 0;
	for (std::string rotor: rotors4){
		std::array<int,26> wirings;
		for (int i = 0; i < rotor.size(); i++){
			wirings[i] = (int) rotor[i] - 64;
		}
		RotorSpecification rot(j,wirings, {});
		j++;
	}
}