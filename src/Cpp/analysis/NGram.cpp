#include "NGram.h"
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/array.hpp>
BiGram::BiGram(std::string filename) {
	frequencies = std::unique_ptr < std::array<float, 1 << (2 * 5)>>(new std::array<float, 1 << (2 * 5)>); //first create frequencies array, and point to with frequencies pointer
	std::ifstream infile(filename,std::ios::binary); //open file
	boost::archive::binary_iarchive ia(infile); //open binary archive with opened file
	ia >> *frequencies;                         //read binary archive into frequencies array
}                                               //file closed when deconstructors are called

float BiGram::score(std::vector<int> word)
{
	std::vector<std::array<int,2>> bigrams = getNGram<int,2>(word);  //get bigrams
	int sum = 0;
	for (std::array<int, 2> bigram : bigrams) {
		int index = 0; //index is the index in frequencies array which this bigram points to
		for (int i = 0; i < 2; i++) {
			index = index | (bigram[i] << (5 * i)); //take the bigram letter (5 bits), move 5 bits per place in bigram, bitwise or with index
		}
		sum +=  (*frequencies)[index]; //look up in frequency table based on this index
	}
	return (float) sum;
}
//trigram and quadgram are functionally the same as bigram, so see BiGram implementation to understand them
TriGram::TriGram(std::string filename) { 
	frequencies = std::unique_ptr < std::array<float, 1 << (3 * 5)>>(new std::array<float, 1 << (3 * 5)>);
	std::ifstream infile(filename, std::ios::binary);
	boost::archive::binary_iarchive ia(infile);
	ia >> *frequencies;
}

float TriGram::score(std::vector<int> word)
{
	std::vector<std::array<int, 3>> bigrams = getNGram<int, 3>(word);
	int sum = 0;
	for (std::array<int, 3> bigram : bigrams) {
		int index = 0;
		for (int i = 0; i < 3; i++) {
			index = index | (bigram[i] << (5 * i));
		}
		sum += (*frequencies)[index];
	}
	return (float)sum;
}

QuadGram::QuadGram(std::string filename) {
	frequencies = std::unique_ptr < std::array<float, 1 << (4 * 5)>>(new std::array<float, 1 << (4 * 5)>);
	std::ifstream infile(filename, std::ios::binary);
	boost::archive::binary_iarchive ia(infile);
	ia >> *frequencies;
}

float QuadGram::score(std::vector<int> word)
{
	std::vector<std::array<int, 4>> bigrams = getNGram<int, 4>(word);
	int sum = 0;
	for (std::array<int, 4> bigram : bigrams) {
		int index = 0;
		for (int i = 0; i < 4; i++) {
			index = index | (bigram[i] << (5 * i));
		}
		sum += (*frequencies)[index];
	}
	return (float)sum;
}