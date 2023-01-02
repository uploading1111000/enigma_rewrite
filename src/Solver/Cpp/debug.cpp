#include "funcs.h"
#include <iostream>

int main() {
	std::vector<int> t{ 1,3,5,2,4,4 };
	std::vector<int> v = sorts::mergesort(t);
	sorts::mergesort(t);
	sorts::mergesort(t);
	sorts::mergesort(t);
	for (int i : v) {
		std::cout << i << ", ";
	}
}