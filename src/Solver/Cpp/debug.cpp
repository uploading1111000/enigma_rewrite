#include "funcs.h"
#include <iostream>

int main() {
	std::vector<int> t{ 1,3,5,2,4,6 };
	std::vector<int> v = sorts::mergesort(t);
	for (int p : v) {
		std::cout << p << ", ";
	}
}