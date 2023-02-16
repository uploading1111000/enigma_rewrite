#include <iostream>
#include <array>
#include "utils/utils.h"
#include "simulation/machineSpecification.h"
#include <set>

int main() {
	MachineSpecification Spec("..../simulation/machineJsons/enigmaI");
	Spec.getRotor(0);
}