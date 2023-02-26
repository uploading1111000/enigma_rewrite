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

    // Serialize the map to a file
    std::ofstream outputFile("output.bin", std::ios::binary);
    boost::archive::binary_oarchive oa(outputFile);
    oa << myMap;

    // Deserialize the map from the file
    std::ifstream inputFile("output.bin", std::ios::binary);
    boost::archive::binary_iarchive ia(inputFile);
    std::map<std::array<int, N>, int> myMap2;
    ia >> myMap2;

    // Print the deserialized map to verify that it was read correctly
    for (auto const& pair : myMap2)
    {
        std::cout << "{";
        for (int i = 0; i < N; i++)
        {
            std::cout << pair.first[i] << " ";
        }
        std::cout << "}: " << pair.second << std::endl;
    }

    return 0;
}