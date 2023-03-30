#include "wirings.h"
#include <string>
#include <set>
#include <array>
#pragma  once
class RotorSpecification : public Wirings{
protected:
	std::array<int, 2> turnpoints; //turnpoint is a set of points at which the rotor will turn the next rotors
public:
	RotorSpecification(int ID);
	RotorSpecification(int ID, std::array<int, 26> wirings, std::array<int,2>);
	RotorSpecification(std::string ID);
	RotorSpecification(std::string ID, std::array<int, 26> wirings, std::array<int,2>);
	std::string getRotorID();
	static std::string getRotorID(int ID);   //static conversion
	using Wirings::getID;
	static int getID(std::string ID);        //static conversion
	std::array<int,2> getTurnpoints() { return turnpoints; };
};