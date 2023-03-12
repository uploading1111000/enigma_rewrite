#include "indexOfCoincidence.h"
#include <array>

class IndexOfCoincidenceOptimised : public IndexOfCoincidence {
public:
	inline float score(std::vector<int> word) {
		std::array<int, 26> frequencies{};
		for (int value : word) {
			frequencies[value - 1]++;
		}
		int sum = 0;
		for (int f : frequencies) {
			sum += f * (f - 1);
		}
		return (float)sum;
	}
};