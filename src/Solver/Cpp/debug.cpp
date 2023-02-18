#include <iostream>
#include <array>
#include "utils/utils.h"
#include "simulation/machineSpecification.h"
#include "machine.h"
#include <set>

int main() {
	MachineSpecification Spec("../../../simulation/machineJsons/enigmaM3.json");
	Machine debugMachine(Spec, { 5,0,6 }, 1, {});
	debugMachine.setPositions({ 11,24,2 });
	debugMachine.setRings({ 21,18,25 });
	std::cout << debugMachine.encryptWord("QUICKBROWNFOX");
}