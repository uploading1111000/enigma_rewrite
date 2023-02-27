#include "NGram.h"
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/array.hpp>
BiGram::BiGram(std::string filename) {
	frequencies = std::unique_ptr < std::array<int, 1 << (2 * 5)>>(new std::array<int, 1 << (2 * 5)>);
	std::ifstream infile(filename,std::ios::binary);
	boost::archive::binary_iarchive ia(infile);
	ia >> *frequencies;
}

float BiGram::score(std::vector<int> word)
{
	std::vector<std::array<int,2>> bigrams = getNGram<int,2>(word);
	int sum = 0;
	for (std::array<int, 2> bigram : bigrams) {
		int index = 0;
		for (int i = 0; i < 2; i++) {
			index = index | (bigram[i] << (5 * i));
		}
		sum +=  (*frequencies)[index];
	}
	return (float) sum / word.size();
}
