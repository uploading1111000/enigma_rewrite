#include "wirings.h"
#include <array>
#include <vector>
#pragma once
#define CONVERT(a) ((int) a) - 64

class Plugboard : public Wirings {
protected:
	std::pair<char, char> last;
public:
	Plugboard(std::array<int, 26> wiring) : Wirings::Wirings(0, wiring) {};
	Plugboard() : Wirings::Wirings(0) {};
	Plugboard(std::vector<std::array<char,2>> letterpairs) : Wirings::Wirings(0) {     //takes in a list of pairs and builds wirings from
		for (auto pair : letterpairs) {                                                //TODO: add() wire pair, temporarily add?
			wiring[CONVERT(pair[0]) - 1] = CONVERT(pair[1]);                                    //TODO: check for repeated letters
			wiring[CONVERT(pair[1]) - 1] = CONVERT(pair[0]);
		}
	}
	void addPlug(std::array<char, 2> pair) {
		wiring[CONVERT(pair[0]) - 1] = CONVERT(pair[1]);                                    //TODO: check for repeated letters
		wiring[CONVERT(pair[1]) - 1] = CONVERT(pair[0]);
		last = { pair[0],pair[1] };
	}
	void removeLast() {
		wiring[CONVERT(last.first) - 1] = CONVERT(last.first);
		wiring[CONVERT(last.second) - 1] = CONVERT(last.second);
	}
};