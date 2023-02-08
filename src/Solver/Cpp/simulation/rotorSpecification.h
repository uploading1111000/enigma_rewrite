#include "wirings.h"
#include <string>
#include <set>
#include <array>
class RotorSpecification : public Wirings{
protected:
	std::set<int> turnpoints; //turnpoint will be a set of points at which the rotor will turn the next one
public:
	RotorSpecification(int ID);
	RotorSpecification(int ID, std::array<int, 26> wirings, std::set<int> turnpoints);
	RotorSpecification(std::string ID);
	RotorSpecification(std::string ID, std::array<int, 26> wirings, std::set<int> turnpoints);
	std::string getRotorID();
	static std::string getRotorID(int ID);   //static conversion
	using Wirings::getID;
	static int getID(std::string ID);        //static conversion
	std::set<int> getTurnpoints() { return turnpoints; };
};