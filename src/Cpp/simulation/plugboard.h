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
			wiring[CONVERT(pair[0]) - 1] = CONVERT(pair[1]);                 //convert from 1 based to 0 based array index on left, 1 based right                  
			wiring[CONVERT(pair[1]) - 1] = CONVERT(pair[0]);
		}
	}
	Plugboard(const Plugboard& copyFrom):Wirings::Wirings(copyFrom) { //remember to reset reverse pointer so old plugboard isn't present on the reverse
		reversePointer.reset();
	};
	void addPlug(std::array<int, 2> pair) { //1 based
		wiring[pair[0] - 1] = pair[1];                                    
		wiring[pair[1] - 1] = pair[0];
		last = { pair[0],pair[1] };
		reversePointer.reset(); //mark dirty
	}
	void removeLast() { //self explanatory
		wiring[last.first-1] = last.first;
		wiring[last.second-1] = last.second;
		reversePointer.reset(); //mark dirty
	}
};