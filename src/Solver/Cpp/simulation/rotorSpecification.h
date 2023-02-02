#include "wirings.h"
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <array>
class RotorSpecification : public Wirings{
private:
	const char romanNumerals[10][6] = { "I","II","III","IV","V","VI","VII","VIII","Beta","Gamma" };
	const std::unordered_map<std::string,int> numeralsRoman =
	{
		{"I",0},
		{"II",1},
		{"III",2},
		{"IV",3},
		{"V",4},
		{"VI",5},
		{"VII",6},
		{"VIII",7},
		{"Beta",8},
		{"Gamma",9}
	};

protected:
	std::unordered_set<int> turnpoints;
public:
	RotorSpecification(int ID);
	RotorSpecification(int ID, std::array<int, 26> wirings, std::unordered_set<int> turnpoints);
	RotorSpecification(std::string ID);
	RotorSpecification(std::string ID, std::array<int, 26> wirings, std::unordered_set<int> turnpoints);
	std::string getRotorID();
	std::string getRotorID(int ID);
	int getIDfromRotor(std::string ID);
};