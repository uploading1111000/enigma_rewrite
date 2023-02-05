#include <array>
#pragma once
class Wirings {
protected:
	int ID;
	std::array<int, 26> wiring;
	Wirings* reversePointer;    //Instead of regenerating a backwards wiring path, a child wiring is created
	void generateReverse(std::array<int, 26> forward);
	int Transform(int in);                                 //Transforms a letter as though going forward through a wiring path
	int TransformReverse(int in);                          //Transforms a letter as though going backward through a wiring path
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
	~Wirings() { 
		delete reversePointer;                             //Child wiring has nullptr so will not delete parent
	};
};