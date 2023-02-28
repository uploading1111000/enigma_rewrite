#include <iostream>
#include "NGram.h"
#include "utils.h"
#include "solverMachine.h"

int main(){
	BiGram bi("../../../ngramData/gramsbi.bin");
	std::cout << bi.score(vectorFromString("AJHKDKHKJH")) << std::endl;
	std::cout << bi.score(vectorFromString("HELLOTHERE")) << std::endl;

	TriGram tri("../../../ngramData/gramstri.bin");
	std::cout << tri.score(vectorFromString("AJHKDKHKJH")) << std::endl;
	std::cout << tri.score(vectorFromString("HELLOTHERE")) << std::endl;

	QuadGram quad("../../../ngramData/gramsquad.bin");
	std::cout << quad.score(vectorFromString("AJHKDKHKJH")) << std::endl;
	std::cout << quad.score(vectorFromString("HELLOTHERE")) << std::endl;
}