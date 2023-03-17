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
    std::string filename = "E:\\Programming\\Project\\data\\final.txt";
    std::string outname = "../../../ngramData/grams";
    std::string datain;
    {
        std::ifstream fin(filename);
        std::getline(fin, datain);
    }
    std::vector<int> data;
    data.reserve(datain.size());
    for (char c : datain) {
        data.push_back((int)c - 64);
    }
    std::vector<std::array<int, 2>> bigrams = getNGram<int,2>(data);
    std::vector<std::array<int, 3>> trigrams = getNGram<int, 3>(data);
    std::vector<std::array<int, 4>> quadgrams = getNGram<int, 4>(data);

    std::array<int, 1024> bigramFrequencies{};
    std::array<int, 32768> trigramFrequencies{};
    std::array<int, 1048576>* quadgramFrequencies = new std::array<int, 1048576>{};

    for (std::array<int, 2> bigram : bigrams) {
        int index = 0;
        for (int i = 0; i < 2; i++) {
            index = index | (bigram[i] << (5 * i));
        }
        bigramFrequencies[index]++;
    }
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
    
    std::array<float, 1024> bigramProbabilities{};
    std::array<float, 32768> trigramProbabilities{};
    std::array<float, 1048576>* quadgramProbabilities = new std::array<float, 1048576>{};
    for (int i = 0; i < 1024; i++) bigramProbabilities[i] = (bigramFrequencies[i] > 1 ? std::log(bigramFrequencies[i]) : 0);
    for (int i = 0; i < 32768; i++) trigramProbabilities[i] = (trigramFrequencies[i] > 1 ? std::log(trigramFrequencies[i]) : 0);
    for (int i = 0; i < 1048576; i++) quadgramProbabilities->at(i) = (quadgramFrequencies->at(i) > 1 ? std::log(quadgramFrequencies->at(i)) : 0);

    {
        std::ofstream outfile(outname + "bi.bin", std::ios::binary);
        boost::archive::binary_oarchive oa(outfile);
        oa << bigramProbabilities;
    }
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


    /*std::map<std::array<int, 3>, int> myMap = {{{1,2,3}, 4}, {{4,5,6}, 7}, {{7,8,9}, 10}};

    std::cout << "checkpoint1\n";
    // Serialize the map to a file
    {
        std::ofstream outputFile("output.bin", std::ios::binary);
        boost::archive::binary_oarchive oa(outputFile);
        boost::serialization::save(oa, myMap, 0);
    }
    std::cout << "checkpoint2\n";
    // Deserialize the map from the file
    {
        std::ifstream inputFile("output.bin", std::ios::binary);
        boost::archive::binary_iarchive ia(inputFile);
        std::map<std::array<int, N>, int> myMap2;
        boost::serialization::load(ia, myMap2, 0);
    }
    std::cout << "checkpoint3\n";*/
    return 0;
}