#include "utils.h"
std::array<int, 26> wiringUtils::arrayFromString(std::string in) {
	if (in.size() != 26) return { -1 };
	std::array<int, 26> returnable;
	for (int i = 0; i < 26; i++) {
		char key = in[i];
		if (!(0 < (int)key - 64 && int(key)-64 < 27)) return {-1};
		returnable[i] = (int)key - 64;
	}
	return returnable;
}

std::vector<int> wiringUtils::vectorFromString(std::string in)
{
	std::vector<int> returnable;
	for (char key : in) {
		if (!(0 < (int)key - 64 < 27)) continue;
		returnable.push_back((int)key - 64);
	}
	return returnable;
}
