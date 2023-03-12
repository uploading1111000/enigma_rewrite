#include "indexOfCoincidence.h"
#include <array>
#include <iostream>

float IndexOfCoincidence::score(std::vector<int> word) {
	std::array<int, 26> frequencies{};
	for (int value : word) {
		frequencies[value - 1]++;
	}
	int sum = 0;
	for (int f : frequencies) {
		sum += f * (f-1);
	}
	int divisor = word.size() * (word.size() - 1); //logically this might not be neccessary because it will be same for all outputs
	return (float) sum / divisor;
}