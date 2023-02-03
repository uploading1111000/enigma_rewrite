#include <iostream>
#include <array>
#include "utils/utils.h"
#include "simulation/rotorSpecification.h"

int main() {
	RotorSpecification v(1);
	int i;
	while (true) {
		std::cin >> i;
		std::cout << v.getRotorID(i) << std::endl;
	}
}