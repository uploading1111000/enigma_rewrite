#include <iostream>
#include <array>
#include "wirings.h"
#include <utils.h>

int main() {
	std::array<int, 26> preset = wiringUtils::arrayFromString("YRUHQSLDPXNGOKMIEBFZCWVJAT");
	std::cout << preset[0] << std::endl;
	Wirings reflector(1, preset);
	int i;
	while (true) {
		std::cin >> i;
		std::cout << reflector.Transform(i) << std::endl;
	}
	return 0;
}