#include <iostream>
#include <array>
#include "utils/utils.h"
#include "simulation/machineSpecification4.h"
#include <set>

int main() {
	MachineSpecificationFour Spec("../../simulation/machineJsons/enigmaM4.json");
	for (int j = 0; j < Spec.getRotorLength(); j++) {
		RotorSpecification A = Spec.getNext();
		std::cout << A.getRotorID() << std::endl;
		for (int i : A.getTurnpoints()) {
			std::cout << i;
		}
		std::cout << std::endl;
		for (int i : A.getWiring()) {
			std::cout << (char)(i + 64);
		}
		std::cout << std::endl;
	}
}