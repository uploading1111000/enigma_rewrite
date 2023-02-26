#include <iostream>
#include "indexOfCoincidence.h"
#include "utils.h"

std::string clean(std::string in) {
	std::string returnable;
	for (int letter : in) {
		if (letter > 64 and letter < 91) returnable.push_back((char)letter);
		else if (letter > 96 and letter < 123) returnable.push_back((char)letter - 32);
	}
	return returnable;
}

#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/array.hpp>

const int N = 3; // size of the array

int main()
{
    std::map<std::array<int, N>, int> myMap = { { {1,2,3}, 4 }, { {4,5,6}, 7 }, { {7,8,9}, 10 } };

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
    std::cout << "checkpoint3\n";
    return 0;
}