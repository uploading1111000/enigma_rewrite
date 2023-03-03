#include "rotorSpecification.h"
#include <unordered_map>
#include <stdexcept>
RotorSpecification::RotorSpecification(int ID)
	: Wirings::Wirings(ID)
{
	turnpoints = { -1,-1 };
}

RotorSpecification::RotorSpecification(int ID, std::array<int, 26> wiringI, std::array<int,2> turnpointsI)
	: Wirings::Wirings(ID,wiringI)
{
	turnpoints = turnpointsI;
}

RotorSpecification::RotorSpecification(std::string ID)
	: Wirings::Wirings(getID(ID))
{
	turnpoints = { -1,-1 };
}

RotorSpecification::RotorSpecification(std::string ID, std::array<int, 26> wiringI, std::array<int,2> turnpointsI)
	: Wirings::Wirings(getID(ID),wiringI)
{
	turnpoints = turnpointsI;
}

std::string RotorSpecification::getRotorID()
{
	return getRotorID(getID());
}

const char romanNumerals[8][6] = { "I","II","III","IV","V","VI","VII","VIII" };

std::string RotorSpecification::getRotorID(int ID)
{
	if (!(ID >= 0 && ID <= 9)) return "";
	return (std::string) romanNumerals[ID];
}

const std::unordered_map<std::string, int> numeralsRoman
{
	{"I",0},
	{"II",1},
	{"III",2},
	{"IV",3},
	{"V",4},
	{"VI",5},
	{"VII",6},
	{"VIII",7},
};

int RotorSpecification::getID(std::string rotor)
{
	try {
		return numeralsRoman.at(rotor);
	}
	catch (std::out_of_range) {
		return -1;
	}

}