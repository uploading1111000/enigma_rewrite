#include "indexOfCoincidence.h"
#include <array>
#include <iostream>

float IndexOfCoincidence::score(std::vector<int> word) { //follows formula given in paper
	std::array<int, 26> frequencies{}; //first frequencies of each letter are found by searching through the text
	for (int value : word) {
		frequencies[value - 1]++;
	}
	int sum = 0; //sum of f*f-1 is then quickly calculated
	for (int f : frequencies) {
		sum += f * (f-1);
	}
	int divisor = word.size() * (word.size() - 1); //this is removed in optimised index of coincidence
	return (float) sum / divisor;
}