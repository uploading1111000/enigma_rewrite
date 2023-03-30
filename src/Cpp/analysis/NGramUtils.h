#include <array>
#include <vector>
#include <memory>

template<typename T,int N> //T determines the type of NGram (int,char) while N defines what the N in Ngram is
std::vector<std::array<T, N>> getNGram(std::vector<T> word) {
	std::vector<std::array<T, N>> returnable;
	returnable.reserve(word.size()); //a word of length m will have m-n ngrams, and reserving space means we don't have to do it multiple times when vector becomes too large
	for (int i = 0; i <= word.size() - N; i++) { // for Ngram start
		std::array<T, N> nGram; //create an Ngram
		for (int j = 0; j < N; j++) { //for j in N
			nGram[j] = word[i + j];  //set the jth letter of Ngram to the jth letter of the NGram in text
		}
		returnable.push_back(nGram); //add ngram to ngrams
	}
	return returnable;
}
