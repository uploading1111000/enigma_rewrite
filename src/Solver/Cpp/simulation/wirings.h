#include <array>
#pragma once
const std::array<int, 26> sequential = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26 };

class Wirings {
protected:
	int ID;
	std::array<int, 26> wiring;
	Wirings* reversePointer;    //Instead of regenerating a backwards wiring path, a child wiring is created
	void generateReverse(std::array<int, 26> forward);
	static inline void normalise(int& in){
		if (in > 26) in -= 26;
		if (in > 26) in -= 26;
		if (in < 1) in += 26;
		if (in < 1) in += 26;
	};
public:
	void setID(int id) {
		ID = id;
	}
	int getID() {
		return ID;
	}
	void reverse();                                        //Creates reversed child wiring
	void setWiring(std::array<int, 26> newWiring) {
		wiring = newWiring;
	}
	std::array<int, 26> getWiring() {
		return wiring;
	}
	Wirings(int ID);
	Wirings(int ID, std::array<int, 26> wiring);
	Wirings();
	~Wirings() { 
		delete reversePointer;                             //Child wiring has nullptr so will not delete parent
	};
	int Transform(int in);                                 //Transforms a letter as though going forward through a wiring path
	int TransformReverse(int in);                          //Transforms a letter as though going backward through a wiring path
};