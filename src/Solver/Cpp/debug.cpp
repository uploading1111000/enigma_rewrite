#include <iostream>
#include <array>
#include <utils.h>
#include "rotorSpecification.h"

int main() {
	RotorSpecification v(1);
	int i;
	while (true) {
		std::cin >> i;
		std::cout << v.getRotorID(i) << std::endl;
	}
}