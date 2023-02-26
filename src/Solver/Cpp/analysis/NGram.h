#include "analysisAbstract.h"
#include "NGramUtils.h"
#include <unordered_map>
#include <string>
template<int N> class NGram {
protected:
	std::unordered_map<std::array<int, N>, int> frequencies;
public:
	NGram(std::string);
	float score(std::vector<int>);
};