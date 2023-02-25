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

int main() {
	/*MachineSpecificationFour Spec("../../../simulation/machineJsons/enigmaM4.json");
	MachineFour debugMachine(Spec, { 2,6,4 }, 0, 1, { {'W','M'},{'E','F'},{'C','K'},{'D','B'}, {'Q','H'}, {'X','Z'}, {'A','J'},{'R','N'},{'U','G'},{'I','V'}});
	debugMachine.setPositions({ 15,19,13 });
	debugMachine.setRings({ 13,4,4 });
	debugMachine.setRotorFourPosition(22);
	debugMachine.setRotorFourRing(3);
	std::cout << debugMachine.encryptWord("PHASELLUSMOLESTIESAPIENEUIMPERDIET");*/
	Analyser* analyser = new IndexOfCoincidence();
	std::cout << analyser->getName() << std::endl;
	std::cout << analyser->score(wiringUtils::vectorFromString(clean("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum ornare, ex non pellentesque egestas, elit nibh consequat orci, in fermentum ex quam at ipsum. Aenean vulputate auctor metus. In ac eros et erat dignissim hendrerit. Ut rutrum tristique felis, nec sodales tellus interdum et. Donec nec elementum tellus, et sagittis nisl. Suspendisse quis risus lectus. Maecenas suscipit bibendum dui."))) << std::endl;
}