#include <iostream>
#include "solverMachine.h"

int main(){
	BiGram hello("E:/Programming/Project/data/gramsbi.bin");
	std::cout << hello.score(vectorFromString("AJHKDKHKJH")) << std::endl;
	std::cout << hello.score(vectorFromString("HELLOTHERE"));
}