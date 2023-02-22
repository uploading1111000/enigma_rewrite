#include "wirings.h"
#include <array>
#include <vector>
#pragma once
#define CONVERT(a) ((int) a) - 64

class Plugboard : public Wirings {
public:
	Plugboard(std::array<int, 26> wiring) : Wirings::Wirings(0, wiring) {};
	Plugboard() : Wirings::Wirings(0) {};
	Plugboard(std::vector<std::array<char,2>> letterpairs) : Wirings::Wirings(0) {     //takes in a list of pairs and builds wirings from
		for (auto pair : letterpairs) {                                                //TODO: add() wire pair, temporarily add?
			wiring[CONVERT(pair[0]) - 1] = CONVERT(pair[1]);                                    //TODO: check for repeated letters
			wiring[CONVERT(pair[1]) - 1] = CONVERT(pair[0]);
		}
	}
};