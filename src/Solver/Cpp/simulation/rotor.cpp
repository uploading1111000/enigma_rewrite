#include "rotor.h"

Rotor::Rotor(int pos, int ring, Place pla, RotorSpecification model):
	RotorSpecification::RotorSpecification(model)
{
	position = pos;
	ringPosition = ring;
	place = pla;
}

Rotor::Rotor(int pos, int ring, RotorSpecification model) :
	RotorSpecification::RotorSpecification(model)
{
	position = pos;
	ringPosition = ring;
	place = turnless;
}

Rotor::Rotor(RotorSpecification model):
	RotorSpecification::RotorSpecification(model)
{
	position = 1;
	ringPosition = 1;
	place = turnless;
}

Rotor::Rotor(int ID):
	RotorSpecification::RotorSpecification(ID)
{
	position = 1;
	ringPosition = 1;
	place = turnless;
}

Rotor::Rotor(std::string ID):
	RotorSpecification::RotorSpecification(ID)
{
	position = 1;
	ringPosition = 1;
	place = turnless;
}

bool Rotor::mutate(bool previous)
{
	bool next = false;
	bool flag = previous;
	switch (place) {
	case left:
		if (turnpoints.contains(position) && flag) {
			next = true;
		}
		break;
	case middle:
		if (turnpoints.contains(position)) {
			flag = true;
			next = true;
		}
		break;
	}
	if (flag) { position = (position < 26) ? position + 1 : 1;}
	return next;
}

int Rotor::forwardTransform(int in)
{
	int toTrans = (in + position - ringPosition) % 26;
	if (toTrans == 0) toTrans = 26;
	int transformed = Transform(toTrans);
	int returnable = (transformed - position + ringPosition) % 26;
	return (returnable != 0) ? returnable : 26;
}

int Rotor::backwardTransform(int in)
{
	int toTrans = (in + position - ringPosition) % 26;
	if (toTrans == 0) toTrans = 26;
	int transformed = TransformReverse(toTrans);
	int returnable = (transformed - position + ringPosition) % 26;
	return (returnable != 0) ? returnable : 26;
}

