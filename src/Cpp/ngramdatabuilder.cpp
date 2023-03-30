#include "NGramUtils.h"
#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <math.h>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/array.hpp>

int main()
{
    std::string filename = "E:\\Programming\\Project\\data\\final.txt"; //this was on my computer
    std::string outname = "../../../ngramData/grams";   //should not be computer specific
    std::string datain;
    {
        std::ifstream fin(filename); //open data file
        std::getline(fin, datain); //put in one, very long, string
    }
    std::vector<int> data; //will store long string as integers
    data.reserve(datain.size());
    for (char c : datain) {
        data.push_back((int)c - 64); //convert string to integers 1-26
    }
    std::vector<std::array<int, 2>> bigrams = getNGram<int,2>(data); //ngram generation done here
    std::vector<std::array<int, 3>> trigrams = getNGram<int, 3>(data);
    std::vector<std::array<int, 4>> quadgrams = getNGram<int, 4>(data); 

    std::array<int, 1024> bigramFrequencies{}; //5 bits of addressing
    std::array<int, 32768> trigramFrequencies{}; //10 bits of addressing
    std::array<int, 1048576>* quadgramFrequencies = new std::array<int, 1048576>{}; //15 bits of addressing. pointer used to allocate on heap not stack

    for (std::array<int, 2> bigram : bigrams) { //per bigram
        int index = 0;
        for (int i = 0; i < 2; i++) {
            index = index | (bigram[i] << (5 * i)); //get bigram index through bitshifts. explained in more detail in NGrams analyser
        }
        bigramFrequencies[index]++; //look up index and increment
    }
    //trigram and quadgram are functionally the same as bigram
    for (std::array<int, 3> trigram : trigrams) {
        int index = 0;
        for (int i = 0; i < 3; i++) {
            index = index | (trigram[i] << (5 * i));
        }
        trigramFrequencies[index]++;
    }
    for (std::array<int, 4> quadgram : quadgrams) {
        int index = 0;
        for (int i = 0; i < 4; i++) {
            index = index | (quadgram[i] << (5 * i));
        }
        quadgramFrequencies->at(index)++;
    }
    //frequencies now need to be converted to logarithms, which makes addition of logarithms the same action as multiplication of frequencies
    //multiplication of frequencies the same action as multiplication of probabilities which is the probability of a string occuring
    std::array<float, 1024> bigramProbabilities{};
    std::array<float, 32768> trigramProbabilities{};
    std::array<float, 1048576>* quadgramProbabilities = new std::array<float, 1048576>{};
    for (int i = 0; i < 1024; i++) bigramProbabilities[i] = (bigramFrequencies[i] > 1 ? std::log(bigramFrequencies[i]) : 0); //log or 0, as log(0) is undefined
    for (int i = 0; i < 32768; i++) trigramProbabilities[i] = (trigramFrequencies[i] > 1 ? std::log(trigramFrequencies[i]) : 0);
    for (int i = 0; i < 1048576; i++) quadgramProbabilities->at(i) = (quadgramFrequencies->at(i) > 1 ? std::log(quadgramFrequencies->at(i)) : 0);

    {
        std::ofstream outfile(outname + "bi.bin", std::ios::binary); //open output file (should create if not found)
        boost::archive::binary_oarchive oa(outfile); //create binary archive from opened file
        oa << bigramProbabilities; //store probabilities array in binary archive
    } //file closed when deconstructors called
    {
        std::ofstream outfile(outname + "tri.bin", std::ios::binary);
        boost::archive::binary_oarchive oa(outfile);
        oa << trigramProbabilities;
    }
    {
        std::ofstream outfile(outname + "quad.bin", std::ios::binary);
        boost::archive::binary_oarchive oa(outfile);
        oa << *quadgramProbabilities;
    }
    return 0;
}