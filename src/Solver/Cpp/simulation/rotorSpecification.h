#include "wirings.h"
#include <string>
#include <unordered_set>
#include <array>
class RotorSpecification : public Wirings{
protected:
	std::unordered_set<int> turnpoints;
public:
	RotorSpecification(int ID);
	RotorSpecification(int ID, std::array<int, 26> wirings, std::unordered_set<int> turnpoints);
	RotorSpecification(std::string ID);
	RotorSpecification(std::string ID, std::array<int, 26> wirings, std::unordered_set<int> turnpoints);
	std::string getRotorID();
	std::string getRotorID(int ID);
	using Wirings::getID;
	int getID(std::string ID);
	std::unordered_set<int> getTurnpoints() { return turnpoints; };
};