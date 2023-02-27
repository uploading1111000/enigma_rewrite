#include "analysisAbstract.h"
#include "NGramUtils.h"
#include <memory>
#include <array>
#include <string>

class BiGram: public Analyser {
protected:
	std::unique_ptr<std::array<int, 1<<(2*5)>> frequencies;
public:
	BiGram(std::string);
	float score(std::vector<int>);
};