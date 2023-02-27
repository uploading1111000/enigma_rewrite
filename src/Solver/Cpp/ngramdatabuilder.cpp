#include "NGramUtils.h"
#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <string>
#include <unordered_map>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/array.hpp>

int main()
{
    std::string filename;
    std::cout << "Filename: ";
    std::cin >> filename;
    std::string outname;
    std::cout << "Output fileprefix: ";
    std::cin >> outname;
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

    std::unordered_map<std::array<int, 2>,int> bigramFrequencies;
    std::unordered_map<std::array<int, 3>, int> trigramFrequencies;
    std::unordered_map<std::array<int, 4>, int> quadgramFrequencies;

    for (std::array<int, 2> key : bigrams) bigramFrequencies[key]++;
    for (std::array<int, 3> key : trigrams) trigramFrequencies[key]++;
    for (std::array<int, 4> key : quadgrams) quadgramFrequencies[key]++;
    {
        std::ofstream biout(outname + "bi.bin");
        boost::archive::binary_oarchive oa(biout);
        boost::serialization::save(oa, bigramFrequencies, 1);
    }
    {
        std::ofstream triout(outname + "tri.bin");
        boost::archive::binary_oarchive oa(triout);
        boost::serialization::save(oa, trigramFrequencies, 1);
    }
    {
        std::ofstream quadout(outname + "quad.bin");
        boost::archive::binary_oarchive oa(quadout);
        boost::serialization::save(oa, quadgramFrequencies, 1);
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