#include "wirings.h"
#include "wirings.h"

int Wirings::Transform(int in)
{
	if (in < 1 || in > 26) return -1; //validation
	return wiring[in - 1];
}

int Wirings::TransformReverse(int in)
{
	if (reversePointer == nullptr) reverse(); //creates reverse wirings if the backward wiring is dirty/uninitialised
	return reversePointer->Transform(in);
}

void Wirings::reverse()
{
	if (reversePointer != nullptr) return;
	reversePointer = std::shared_ptr<Wirings>(new Wirings(ID)); //create reverse wiring object
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

Wirings::Wirings()
{
	ID = 0;
	wiring = sequential;
	reversePointer = nullptr;
}

void Wirings::generateReverse(std::array<int, 26> forward) //takes forward wirings and creates backwards, before setting self
{
	for (int i = 1; i <= 26;i++) {
		int f = forward[i - 1]; //forward i -> f
		wiring[f - 1] = i; //backward f -> i
	}
}
