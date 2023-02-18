#include "rotorSpecification.h"
#pragma once
enum Place {
	right = 2,   //1st rotor, will turn next rotor if in correct position
	middle = 1,  //2nd rotor, will turn one after if in the correct position and then always turn self (double step)
	left = 0, //3rd rotor, will turn but not effect 4th
	turnless  //turnless will encompass 4th rotor and debugging, will still turn but not effect next.
};


class Rotor : public RotorSpecification {
protected:
	int position = 1;                     //1 is A is base position
	int ringPosition = 1;                 //1 is base position (unlike emulator which incorrectly uses 0
	Place place = turnless;               //storing position of rotor allows mutate to be self contained
public:
	Rotor(int, int, Place,const RotorSpecification&);
	Rotor(int, int, const RotorSpecification&);
	Rotor(const RotorSpecification&);
	Rotor(int);
	Rotor(std::string);
	Rotor();
	bool mutate(bool);               //takes in a boolean of whether to turn, and determines whether next rotor turns
	int Transform(int);       //first pass through rotors
	int TransformReverse(int);      //second pass through rotors
	int getPosition() { return position; };
	void setPosition(int in) { position = in; };
	void setRing(int in) { ringPosition = in; };
	int getRingPosition() { return ringPosition; };
};