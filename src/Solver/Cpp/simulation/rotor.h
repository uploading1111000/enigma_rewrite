#include "rotorSpecification.h"
enum Place {
	right = 0,
	middle = 1,
	left = 2,
	turnless
};


class Rotor : public RotorSpecification {
protected:
	int position;
	int ringPosition;
	Place place;
public:
	Rotor(int, int, Place,RotorSpecification);
	Rotor(int, int, RotorSpecification);
	Rotor(RotorSpecification);
	Rotor(int);
	Rotor(std::string);
	bool mutate(bool);
	int forwardTransform(int);
	int backwardTransform(int);
	int getPosition() { return position; };
	int getRingPosition() { return ringPosition; };
};