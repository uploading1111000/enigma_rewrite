#include <iostream>
#include "indexOfCoincidence.h"
#include "utils.h"
#include "NGram.h"
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/array.hpp>

std::string clean(std::string in) {
	std::string returnable;
	for (int letter : in) {
		if (letter > 64 and letter < 91) returnable.push_back((char)letter);
		else if (letter > 96 and letter < 123) returnable.push_back((char)letter - 32);
	}
	return returnable;
}

const int N = 2;
int main(){
	BiGram hello("E:/Programming/Project/data/gramsbi.bin");
	std::cout << hello.score(vectorFromString("AJHKDKHKJH")) << std::endl;
	std::cout << hello.score(vectorFromString("HELLOTHERE"));
}