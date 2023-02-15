#include <iostream>
#include <array>
#include "utils/utils.h"
#include "simulation/rotor.h"
#include <set>

int main() {
	std::array<int, 26> wires = wiringUtils::arrayFromString("EKMFLGDQVZNTOWYHXUSPAIBRCJ");
	Wirings wiring(1, wires);
	RotorSpecification spec(1, wires, { (int)'Q' - 65 });
	
	Rotor rotor(spec);
	for (int t : wiring.getWiring()) {
		std::cout << t << "\n";
	}
	char letter;
	while (true) {

		std::cout << "key to transform: ";
		std::cin >> letter;
		int i = (int) letter - 64;
		rotor.mutate(true);
		int result = rotor.forwardTransform(i);
		std::cout << "result: " << (char) (result + 64) << std::endl;
		std::cout << "rotor position: " << rotor.getPosition() << std::endl;
	}
}