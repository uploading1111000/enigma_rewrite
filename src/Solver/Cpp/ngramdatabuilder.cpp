#include "NGramUtils.h"
#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <string>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/array.hpp>

int main()
{
    std::string filename;
    std::cout << "Filename: ";
    std::cin >> filename;
    std::string datain;
    std::ifstream fin(filename);
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