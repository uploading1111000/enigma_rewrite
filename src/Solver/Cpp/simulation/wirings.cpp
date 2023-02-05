#include "wirings.h"

const std::array<int, 26> sequential = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};

int Wirings::Transform(int in)
{
	if (in < 1 || in > 26) return -1;
	return wiring[in - 1];
}

int Wirings::TransformReverse(int in)
{
	if (reversePointer == nullptr) reverse();
	return reversePointer->Transform(in);
}

void Wirings::reverse()
{
	if (reversePointer != nullptr) return;
	reversePointer = new Wirings(ID);
	reversePointer->generateReverse(this->wiring);
}

Wirings::Wirings(int id)
{
	ID = id;
	wiring = sequential;
	reversePointer = nullptr;
}

Wirings::Wirings(int id, std::array<int, 26> Iwiring)
{
	wiring = Iwiring;
	ID = id;
	reversePointer = nullptr;
}

void Wirings::generateReverse(std::array<int, 26> forward)
{
	for (int i = 1; i <= 26;i++) {
		int f = forward[i - 1];
		wiring[f - 1] = i;
	}
}
