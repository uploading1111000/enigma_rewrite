#include <vector>
#include <string>
#pragma once

class Analyser { //abstract analyser class, allowing polymorphic use of different analyser machines
public:
	virtual float score(std::vector<int>) { return 0; }; //scores a vector of integers, which represents a text
	virtual std::string getName() { return "Unknown"; }; //was potentially intended to be used to get the name of an analyser
};