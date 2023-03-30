#include "machine.h"
#include "machine.h"
#include "machine.h"
#include "machine.h"
#include "machine.h"
#include "machine.h"

//converts take a character and convert to 1-26 or the other way
inline int convert(char in) {
	return (int) in - 64;
}

inline char convert(int in) {
	return (char)in + 64;
}

Machine::Machine(MachineSpecification& spec, std::array<int, 3> rotorIds, int reflectorId, std::vector<std::array<char, 2>> plugboardPairs)
{
	specification = &spec;
	setRotors(rotorIds); //important to use this instead of just setting the rotors directly
	reflector = specification->getReflector(reflectorId);
	plugboard = Plugboard(plugboardPairs);
}

void Machine::incrementRotor(int N) {
	int curr = rotors[N].getID(); //current id
	curr++; //increment
	if (curr >= this->getSpecification()->getRotorLength()) { //wrap around
		curr = 0;
	}
	setRotor(N, curr);
}
void Machine::decrementRotor(int N) {
	int curr = rotors[N].getID();
	curr--;
	if (curr < 0) {
		curr = this->getSpecification()->getRotorLength()-1;
	}
	setRotor(N, curr);
}

void Machine::setPositions(std::array<int, 3> positions)
{
	for (int i = 0; i < 3; i++) {
		setPosition(i, positions[i]);
	}
}

void Machine::setPosition(int N, int position)
{
	rotors[N].setPosition(position);
}

void Machine::setRings(std::array<int, 3> rings)
{
	for (int i = 0; i < 3; i++) {
		setRing(i, rings[i]);
	}
}

void Machine::setRing(int N, int ring)
{
	rotors[N].setRing(ring);
}

void Machine::setRotor(Place place, int id)
{
	rotors[place] = Rotor(this->getSpecification()->getRotor(id), place);
}

void Machine::setRotor(int place, int id)
{
	switch (place) { //have to use a switch because i had errors when converting an int to a place, but not the other way for some reason
	case 0:
		rotors[place] = Rotor(this->getSpecification()->getRotor(id), left);
		break;
	case 1:
		rotors[place] = Rotor(this->getSpecification()->getRotor(id), middle);
		break;
	case 2:
		rotors[place] = Rotor(this->getSpecification()->getRotor(id), right);
		break;
	default:
		rotors[place] = Rotor(this->getSpecification()->getRotor(id), turnless);
		break;
	}
	
}

void Machine::setRotors(std::array<int,3> ids)
{
	for (int i = 0; i < 3; i++) {
		setRotor(i, ids[i]);
	}
}

void Machine::mutateRotors()  //mutates are chained into one another, with the result from each mutate determining whether to rotate the next
{
	rotors[left].mutate(
		rotors[middle].mutate(
			rotors[right].mutate(true)
		)
	);
}

int Machine::encryptLetter(int start)
{
	mutateRotors();                                         //mutate
	int plugF = plugboard.Transform(start);                 //plugboard forward
	int rightF = rotors[right].Transform(plugF);            //rotors forward
	int middleF = rotors[middle].Transform(rightF);
	int leftF = rotors[left].Transform(middleF);
	//int fourthF = rotorFour.Transform(leftF)
	int reflected = reflector.Transform(leftF);             //reflector
	//int fourthR = rotorFour.TransformReverse(reflected)
	int leftR = rotors[left].TransformReverse(reflected);   //rotors backward
	int middleR = rotors[middle].TransformReverse(leftR);
	int rightR = rotors[right].TransformReverse(middleR);
	return plugboard.TransformReverse(rightR);              //plugboard backward and return
}

char Machine::encryptLetter(char letter) //wrapper around the int method, converting letters to integers and back
{
	int start = convert(letter);
	int out = start;
	if (start > 0 and start < 27) out = this->encryptLetter(start);     //capitals
	else if (start > 32 and start < 59) out = this->encryptLetter(start - 32);  //lower case
	return convert(out);
}

std::vector<int> Machine::encryptWord(std::vector<int> input)  //wrapper around int method, performing encrypt on each int
{
	std::vector<int> returnable;
	for (int start : input) {
		int out = this->encryptLetter(start);
		returnable.push_back(out);
	}
	return returnable;
}

std::string Machine::encryptWord(std::string word)   //wrapper around int method, through char method
{
	std::string returnable;
	for (char letter : word) {
		returnable.push_back(encryptLetter(letter));
	}
	return returnable;
}

std::vector<int> Machine::encryptLetterVerbose(int start)  //visualiser method
{
	std::vector<int> returnable;  //returnable is the vector of letters the decryption goes through
	returnable.push_back(start);  //after each encryption step the letter is pushed to end of returnable
	mutateRotors();               //otherwise the same as the normal int encrypt
	int plugF = plugboard.Transform(start);
	returnable.push_back(plugF);
	int rightF = rotors[right].Transform(plugF);
	returnable.push_back(rightF);
	int middleF = rotors[middle].Transform(rightF);
	returnable.push_back(middleF);
	int leftF = rotors[left].Transform(middleF);
	returnable.push_back(leftF);
	returnable.push_back(leftF);       //double push back to make same length as 4 rotors for visualisation
	//int fourthF = rotorFour.Transform(leftF)
	int reflected = reflector.Transform(leftF);
	returnable.push_back(reflected);   //double push back to make same length as 4 rotors for visualisation
	returnable.push_back(reflected);
	//int fourthR = rotorFour.TransformReverse(reflected)
	int leftR = rotors[left].TransformReverse(reflected);
	returnable.push_back(leftR);
	int middleR = rotors[middle].TransformReverse(leftR);
	returnable.push_back(middleR);
	int rightR = rotors[right].TransformReverse(middleR);
	returnable.push_back(rightR);
	int plugR = plugboard.TransformReverse(rightR);
	returnable.push_back(plugR);
	return returnable;
}

std::string Machine::encryptLetterVerbose(char letter) //wrapper around int visualiser encrypt
{
	int start = convert(letter);
	std::vector<int> result = this->encryptLetterVerbose(start);
	std::string returnable;
	for (int num : result) {
		returnable.push_back(convert(num));
	}
	return returnable;
}

std::array<int, 26> Machine::getWiring(int N) {
	if (N == 0) { //reflector
		return sequential;
	}
	else if (N == 1) { //4th rotor
		return this->getFourth();
	}
	else if (N >= 2 && N <= 4) {
		std::array<int,26> normal = rotors[N - 2].getWiring(); 
		std::array<int, 26> returnable;
		for (int i = 1; i < 27; i++) {         //wiring internally is stack (doesn't account for position) so each letter needs to be
			int indexA = i - rotors[N-2].getPosition() + rotors[N-2].getRingPosition();  //moved downward by position and upward by rings
			int indexB = normal[i-1] - rotors[N-2].getPosition() + rotors[N-2].getRingPosition(); //on both sides, indexA = start, indexB = end of wire
			normalise(indexA);
			normalise(indexB); //normalised back to 1-26
			returnable[indexA - 1] = indexB;
		}
		return returnable;
	}
	else {
		return plugboard.getWiring();
	}
}

void Machine::incrementPosition(int N) {
	int prePos = rotors[N].getPosition() + 1;  //take position
	normalise(prePos);                         //normalise
	rotors[N].setPosition(prePos);             //set
}

void Machine::decrementPosition(int N) {
	int prePos = rotors[N].getPosition() - 1;
	normalise(prePos);
	rotors[N].setPosition(prePos);
}

void Machine::incrementRing(int N) {
	int preRing = rotors[N].getRingPosition() + 1;
	normalise(preRing);
	rotors[N].setRing(preRing);
}

void Machine::decrementRing(int N) {
	int preRing = rotors[N].getRingPosition() - 1;
	normalise(preRing);
	rotors[N].setRing(preRing);
}

void Machine::setPlugboard(std::vector<std::array<char, 2>> letterpairs)
{
	plugboard = Plugboard(letterpairs);
}

std::vector<int> Machine::getTurnpoints(int N) {
	std::array<int, 2> raw = rotors[N].getTurnpoints();
	std::vector<int> returnable;
	for (int val : raw) {
		if (val != 0) { //0 is used to note a turnpoint that doesn't exist, as turnpoints are stored as 2 numbers
			int real = val - rotors[N].getPosition();  //turnpoints are static, so much be adjusted in line with the position
			normalise(real);
			returnable.push_back(real);
		}
	}
	return returnable;
}