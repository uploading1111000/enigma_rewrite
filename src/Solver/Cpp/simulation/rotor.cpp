#include "rotor.h"
#include "rotor.h"
#include <iostream>

Rotor::Rotor(int pos, int ring, Place pla, const RotorSpecification &model):
	RotorSpecification::RotorSpecification(model)
{
	position = pos;
	ringPosition = ring;
	place = pla;
}

Rotor::Rotor(int pos, int ring, const RotorSpecification &model) :
	RotorSpecification::RotorSpecification(model)
{
	position = pos;
	ringPosition = ring;
}

Rotor::Rotor(RotorSpecification const &model):
	RotorSpecification::RotorSpecification(model)
{
}

Rotor::Rotor(const RotorSpecification& model, Place pIn):
	RotorSpecification::RotorSpecification(model)
{
	place = pIn;
}

Rotor::Rotor(int ID):
	RotorSpecification::RotorSpecification(ID)
{
}

Rotor::Rotor(std::string ID):
	RotorSpecification::RotorSpecification(ID)
{
}

Rotor::Rotor() :
	RotorSpecification::RotorSpecification(0)
{
}

bool Rotor::mutate(bool previous)
{
	bool next = false;
	bool flag = previous;
	switch (place) {
	case left:
		if ((turnpoints[0]==position || turnpoints[1] == position) && flag) {
			next = true;
		}
		break;
	case middle:
		if (turnpoints[0] == position || turnpoints[1] == position) {
			flag = true;
			next = true;
		}
		break;
	}
	if (flag) { position = (position < 26) ? position + 1 : 1;}
	return next;
}

int Rotor::Transform(int in)
{
	int toTrans = in + position - ringPosition;
	normalise(toTrans);
	int transformed = Wirings::Transform(toTrans);
	int returnable = transformed - position + ringPosition;
	normalise(returnable);
	return returnable;
}

int Rotor::TransformReverse(int in)
{
	int toTrans = in + position - ringPosition;
	normalise(toTrans);
	int transformed = Wirings::TransformReverse(toTrans);
	int returnable = transformed - position + ringPosition;
	normalise(returnable);
	return returnable;
}

