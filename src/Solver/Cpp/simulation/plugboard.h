#include "wirings.h"
#include <array>
#include <vector>
class Plugboard : public Wirings {
public:
	Plugboard(std::array<int, 26> wiring) : Wirings::Wirings(0, wiring) {};
	Plugboard() : Wirings::Wirings(0) {};
	Plugboard(std::vector<std::array<char,2>> letterpairs) : Wirings::Wirings(0) {
		for (auto pair : letterpairs) {
			wiring[pair[0]] = wiring[pair[1]];
			wiring[pair[1]] = wiring[pair[0]];
		}
	}
};