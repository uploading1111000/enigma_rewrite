#include "wirings.h"
#include <array>
#include <vector>
#pragma once
#define CONVERT(a) ((int) a) - 64

class Plugboard : public Wirings {
protected:
	std::pair<int, int> last; //1 based
public:
	Plugboard(std::array<int, 26> wiring) : Wirings::Wirings(0, wiring) {};
	Plugboard() : Wirings::Wirings(0) {};
	Plugboard(std::vector<std::array<char,2>> letterpairs) : Wirings::Wirings(0) {     //takes in a list of pairs and builds wirings from
		for (auto pair : letterpairs) {                                                
			wiring[CONVERT(pair[0]) - 1] = CONVERT(pair[1]);                                    //TODO: check for repeated letters
			wiring[CONVERT(pair[1]) - 1] = CONVERT(pair[0]);
		}
	}
	void addPlug(std::array<char, 2> pair) { //65 = 1
		wiring[CONVERT(pair[0]) - 1] = CONVERT(pair[1]);                                    //TODO: check for repeated letters
		wiring[CONVERT(pair[1]) - 1] = CONVERT(pair[0]);
		last = { (int) pair[0]-64,(int) pair[1]-64 };
	}
	void addPlug(std::array<int, 2> pair) { //1 based
		wiring[pair[0] - 1] = pair[1];                                    //TODO: check for repeated letters
		wiring[pair[1] - 1] = pair[0];
		last = { pair[0],pair[1] };
	}
	void removeLast() {
		wiring[last.first-1] = last.first;
		wiring[last.second-1] = last.second;
	}
};