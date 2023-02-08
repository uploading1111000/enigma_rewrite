#include "rotorSpecification.h"
enum Place {
	right = 0,   //1st rotor, will turn next rotor if in correct position
	middle = 1,  //2nd rotor, will turn one after if in the correct position and then always turn self (double step)
	left = 2, //3rd rotor, will turn but not effect 4th
	turnless  //turnless will encompass 4th rotor and debugging, will still turn but not effect next.
};


class Rotor : public RotorSpecification {
protected:
	int position = 1;                     //1 is A is base position
	int ringPosition = 1;                 //1 is base position (unlike emulator which incorrectly uses 0
	Place place = turnless;               //storing position of rotor allows mutate to be self contained
public:
	Rotor(int, int, Place,RotorSpecification);
	Rotor(int, int, RotorSpecification);
	Rotor(RotorSpecification);
	Rotor(int);
	Rotor(std::string);
	bool mutate(bool);               //takes in a boolean of whether to turn, and determines whether next rotor turns
	int forwardTransform(int);       //first pass through rotors
	int backwardTransform(int);      //second pass through rotors
	int getPosition() { return position; };
	int getRingPosition() { return ringPosition; };
};