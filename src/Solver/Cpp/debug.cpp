#include <iostream>
#include "indexOfCoincidence.h"
#include "utils.h"

std::string clean(std::string in) {
	std::string returnable;
	for (int letter : in) {
		if (letter > 64 and letter < 91) returnable.push_back((char)letter);
		else if (letter > 96 and letter < 123) returnable.push_back((char)letter - 32);
	}
	return returnable;
}

const int N = 3; // size of the array

int main(){

    return 0;
}