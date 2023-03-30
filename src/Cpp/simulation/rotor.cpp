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

bool Rotor::mutate(bool previous) //mutates the rotor based on whether the previous rotor allows/ says it should move
{
	bool next = false; 
	bool flag = previous; //flag used so rotor can only step once at the end
	switch (place) {
	case right:
		if ((turnpoints[0]==position || turnpoints[1] == position) && flag) {
			next = true;
		}
		break;
	case middle:
		if (turnpoints[0] == position || turnpoints[1] == position) { //double stepping
			flag = true;
			next = true;
		}
		break;
	}
	if (flag) { position = (position < 26) ? position + 1 : 1;} //increment. conditional statement does rollover
	return next;
}

int Rotor::Transform(int in)
{
	int toTrans = in + position - ringPosition; //correct input on right for the position and rings
	normalise(toTrans); 
	int transformed = Wirings::Transform(toTrans); //send to static wires
	int returnable = transformed - position + ringPosition; //correct out on left for the position and rings
	normalise(returnable);
	return returnable;
}

int Rotor::TransformReverse(int in)
{
	int toTrans = in + position - ringPosition; //correct input on left for position and rings
	normalise(toTrans);
	int transformed = Wirings::TransformReverse(toTrans); //send to static wires
	int returnable = transformed - position + ringPosition; //correct output on right for position and rings
	normalise(returnable);
	return returnable;
}

