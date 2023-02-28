#include "analysisAbstract.h"
#include "NGramUtils.h"
#include <memory>
#include <array>
#include <string>

class BiGram: public Analyser {
protected:
	std::unique_ptr<std::array<float, 1<<(2*5)>> frequencies;
public:
	BiGram(std::string);
	float score(std::vector<int>);
};

class TriGram : public Analyser {
protected:
	std::unique_ptr<std::array<float, 1 << (3 * 5)>> frequencies;
public:
	TriGram(std::string);
	float score(std::vector<int>);
};

class QuadGram : public Analyser {
protected:
	std::unique_ptr<std::array<float, 1 << (4 * 5)>> frequencies;
public:
	QuadGram(std::string);
	float score(std::vector<int>);
};