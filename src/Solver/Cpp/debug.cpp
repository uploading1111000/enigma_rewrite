#include <iostream>
#include <array>
#include "utils/utils.h"
#include "simulation/machineSpecification.h"
#include "machine.h"
#include <set>

int main() {
	MachineSpecification Spec("../../../simulation/machineJsons/enigmaM3.json");
	Machine debugMachine(Spec, { 1,0,2 }, 1, { {'E','Z'},{'R','W'},{'M','V'},{'I','U'}, {'B','L'}, {'P','X'}, {'J','O'} });
	debugMachine.setPositions({ 2,7,9 });
	debugMachine.setRings({ 1,23,4 });
	std::cout << debugMachine.encryptWord("AUFBEFEHLDESOBERSTENBEFEHLSHABERSSINDIMFALLEXZXZTX");
}