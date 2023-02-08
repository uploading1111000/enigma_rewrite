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
	int i;
	while (true) {

		std::cout << "num to transform: ";
		std::cin >> i;
		rotor.mutate(true);
		int result = rotor.forwardTransform(i);
		std::cout << "result: " << result << std::endl;
		std::cout << "rotor position: " << rotor.getPosition() << std::endl;
	}
}