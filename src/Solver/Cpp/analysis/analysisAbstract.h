#include <vector>
#include <string>
#pragma once

class Analyser {
public:
	virtual float score(std::vector<int>) { return 0; };
	virtual std::string getName() { return "Unknown"; };
};