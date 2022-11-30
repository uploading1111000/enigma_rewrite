#include "funcs.h"
#include <iostream>

int main() {
	item t(0, 1);
	for (int i = 0; i < 10; i++) {
		std::cout << t.calc(i) << "\n";
	}
}