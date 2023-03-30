#include "utils.h"
std::array<int, 26> arrayFromString(std::string in) //turns a wiring string into an int array the system can work with. used earlier in project
{
	if (in.size() != 26) return { -1 }; //validation
	std::array<int, 26> returnable;
	for (int i = 0; i < 26; i++) {
		char key = in[i];
		if (!(0 < (int)key - 64 && int(key) - 64 < 27)) return { -1 }; // validation
		returnable[i] = (int)key - 64; //convert char to int 1-26
	}
	return returnable;
}

std::vector<int> vectorFromString(std::string in) //turns any string into a vector of ints 1-26
{
	std::vector<int> returnable;
	for (char key : in) {
		if (!(0 < (int)key - 64 < 27)) continue; //validation
		returnable.push_back((int)key - 64); //convert char to int 1-26
	}
	return returnable;
}

std::vector<int> random(int n) //create a random vector of ints 1-26 of length n
{
	std::vector<int> returnable;
	for (int i = 0; i < n; i++) {
		int r = 1 + (rand() % 26); //rand returns value 1-2^16, so modulo takes it back to 0-25, then +1 to get 1-26
		returnable.push_back(r);
	}
	return returnable;
}
