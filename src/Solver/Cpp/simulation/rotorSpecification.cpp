#include "rotorSpecification.h"
#include <iostream>

RotorSpecification::RotorSpecification(int ID)
	: Wirings::Wirings(ID)
{
}

RotorSpecification::RotorSpecification(int ID, std::array<int, 26> wiringI, std::unordered_set<int> turnpointsI)
	: Wirings::Wirings(ID,wiring)
{
	turnpoints = turnpointsI;
	wiring = wiringI;
}

RotorSpecification::RotorSpecification(std::string ID)
	: Wirings::Wirings(getIDfromRotor(ID))
{
}

RotorSpecification::RotorSpecification(std::string ID, std::array<int, 26> wiringI, std::unordered_set<int> turnpointsI)
	: Wirings::Wirings(getIDfromRotor(ID),wiring)
{
	turnpoints = turnpointsI;
	wiring = wiringI;
}

std::string RotorSpecification::getRotorID()
{
	return getRotorID(getID());
}

std::string RotorSpecification::getRotorID(int ID)
{
	if (!(ID >= 0 && ID <= 9)) return "";
	return (std::string) romanNumerals[ID];
}

int RotorSpecification::getIDfromRotor(std::string rotor)
{
	return numeralsRoman.at(rotor);
}
