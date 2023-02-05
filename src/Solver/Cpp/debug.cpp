#include <iostream>
#include <array>
#include "utils/utils.h"
#include "simulation/rotor.h"

int main() {
	Rotor rotor(1);
	int i;
	while (true) {
		std::cout << "num to transform: ";
		std::cin >> i;
		std::cout << "result: " << rotor.forwardTransform(i) << std::endl;
		rotor.mutate(true);
		std::cout << "rotor position: " << rotor.getPosition() << std::endl;
	}
}