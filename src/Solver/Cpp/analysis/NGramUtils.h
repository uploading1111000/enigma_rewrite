#include <array>
#include <vector>

template<typename T,int N>
std::vector<std::array<T, N>> getNGram(std::vector<T> word) {
	std::vector<std::array<T, N>> returnable;
	returnable.reserve(word.size());
	for (int i = 0; i <= word.size() - N; i++) {
		std::array<T, N> nGram;
		for (int j = 0; j < N; j++) {
			nGram[j] = word[i + j];
		}
		returnable.push_back(nGram);
	}
	return returnable;
}