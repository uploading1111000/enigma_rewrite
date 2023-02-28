#include <iostream>
#include <set>
#include "NGram.h"
#include "utils.h"
#include "solverMachine.h"
#include "machine.h"

std::string clean(std::string in) {
	std::string returnable;
	for (int letter : in) {
		if (letter > 64 and letter < 91) returnable.push_back((char)letter);
		else if (letter > 96 and letter < 123) returnable.push_back((char)letter - 32);
	}
	return returnable;
}

int main(){
	TriGram tri("../../../ngramData/gramstri.bin");
	MachineSpecification spec("../../../simulation/machineJsons/EnigmaI.json");
	std::string start;
	std::getline(std::cin, start);
	start = clean(start);
	std::cout << start.size() << std::endl;
	std::vector<std::array<char, 2>> plugs;
	std::set<int> used;
	std::pair<int, std::array<int, 2>> max = {0,{0,0}};
	int j = 0;
	for (int i = 0; i < 6; i++) {
		for (int a = 65; a < 91; a++) {
			if (!used.contains((char)a)) {
				for (int b = 65; b < 91; b++) {
					if (!used.contains((char)b) && a != b) {
						plugs.push_back({ (char)a,(char)b });
						Machine machine(spec, { 2,1,0 }, 1, plugs);
						std::vector<int> result = machine.encryptWord(vectorFromString(start));
						j++;
						float score = tri.score(result);
						if (score > max.first) {
							max.first = score;
							max.second = { a,b };
						}
						plugs.pop_back();
					}
				}
			}
		}
		plugs.push_back({ (char)max.second[0],(char)max.second[1] });
		used.insert(max.second[0]);
		used.insert(max.second[1]);
		std::cout << "max plug: " << (char) max.second[0] << (char) max.second[1] << std::endl;
		Machine machine(spec, { 2,1,0 }, 1, plugs);
		std::string phrase = machine.encryptWord(start);
		std::cout << "score: " << max.first << std::endl;
		std::cout << "phrase: " << phrase << std::endl;
	}
	std::cout << j;
	return 0;
}