#include "analysisAbstract.h"
#include <vector>

class IndexOfCoincidence : public Analyser {
public:
	virtual float score(std::vector<int>);
	std::string getName() { return "Index of Co-incidence"; };
};