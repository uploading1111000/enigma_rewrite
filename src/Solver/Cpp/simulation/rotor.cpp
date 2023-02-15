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
}

Rotor::Rotor(RotorSpecification model):
	RotorSpecification::RotorSpecification(model)
{
}

Rotor::Rotor(int ID):
	RotorSpecification::RotorSpecification(ID)
{
}

Rotor::Rotor(std::string ID):
	RotorSpecification::RotorSpecification(ID)
{
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
	int toTrans = in + position - ringPosition;
	normalise(toTrans);
	int transformed = Transform(toTrans);
	int returnable = transformed - position + ringPosition;
	normalise(returnable);
	return returnable;
}

int Rotor::backwardTransform(int in)
{
	int toTrans = in + position - ringPosition;
	normalise(toTrans);
	int transformed = TransformReverse(toTrans);
	int returnable = transformed - position + ringPosition;
	normalise(returnable);
	return returnable;
}

