#include <iostream>
#include <array>
#include "utils/utils.h"
#include "simulation/machineSpecification4.h"
#include "machine4.h"
#include <set>

int main() {
	MachineSpecificationFour Spec("../../../simulation/machineJsons/enigmaM4.json");
	std::cout << Spec.getRotor(6).getID();
	MachineFour debugMachine(Spec, { 2,6,4 }, 1, 1, { {'W','M'},{'E','F'},{'C','K'},{'D','B'}, {'Q','H'}, {'X','Z'}, {'A','J'},{'R','N'},{'U','G'},{'I','V'}});
	debugMachine.setPositions({ 15,19,13 });
	debugMachine.setRings({ 13,4,4 });
	debugMachine.setRotorFourPosition(3);
	debugMachine.setRotorFourRing(19);
	std::cout << debugMachine.encryptWord("WALTZBADNYMPHFORQUICKJIGSVEX");
}