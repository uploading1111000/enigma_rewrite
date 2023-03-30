#include "solverMachine.h"
#include <iostream>


SolverMachine::SolverMachine(MachineSpecification& spec, std::optional<std::array<int,3>> rotorIndexes, std::optional<int> reflector, 
		std::optional<std::vector<std::array<char, 2>>> plugPairs, std::string ciphertextIn, Analyser* analyserIn):
		Machine::Machine(spec,rotorIndexes ? rotorIndexes.value() : std::array<int,3>{2, 1, 0}, reflector ? reflector.value() : 1, plugPairs ? plugPairs.value() : std::vector<std::array<char,2>>{}) {
	//Machine constructor is called with the optional values if they exist, or a series of default initialisers if they don't
	ciphertext = vectorFromString(ciphertextIn);
	analyser = analyserIn;
}

SolverMachine::SolverMachine() //empty constructor was used for solvermachine4 shenanigans - try not to use
{
}

float SolverMachine::findBestRotors(){
	maxSetting max{ {},{},0 }; 
	int numberOfRotors = this->getSpecification()->getRotorLength();  //get number of rotors available once, and don't have to repeatedly look up
	int totalL = numberOfRotors * (numberOfRotors - 1) * (numberOfRotors - 2); //used in the std::cout
	int j = 0; //used in the std::cout
	for (int l = 0; l < numberOfRotors; l++){ //all left rotors
		setRotor(left, l);
		for (int m = 0; m < numberOfRotors; m++){ //all middle rotors
			if (m==l) continue; //ignore rotor combos where more than 1 rotor of same type used
			setRotor(middle, m);
			for (int r = 0; r < numberOfRotors; r++){ //all right rotors
				if (r == l || r == m) continue; //ignore rotor combos where more than 1 rotor of same type used
				setRotor(right, r);
				maxPosition best = findBestPositions(); //find best position given rotors
				std::cout << best.score << " " << rotors[left].getRotorID() << " " << rotors[middle].getRotorID() << " " << rotors[right].getRotorID() << "\n";
				std::cout << j++ << " / " << totalL << "\n"; //command prompt output
				if (best.score > max.score){ //if less, this result is unimportant
					max = {{l,m,r},best.pos,best.score}; //replace old best score/positions if new is better
				}
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		setRotor(i, max.rotors[i]); //set for further encrypts
		initialPositions[i] = max.pos[i]; //set for further encrypts
	}
	homePosition(); //go to intial positions so python can encrypt ciphertext and give output
	return max.score;
}

float SolverMachine::findBestRings()
{
	maxRings max = { {},0 };
	for (int r = 1; r < 27; r++) { //iterate over all right rings
		for (int m = 1; m < 27; m++) { //iterate over all middle rings (left has no effect)
			rotors[right].setRing(r);
			int rpos = initialPositions[right] + r - 1; //adjust position in line with rings so that wirings are in correct position
			normalise(rpos);
			rotors[right].setPosition(rpos);
			rotors[middle].setRing(m);
			int mpos = initialPositions[middle] + m - 1; //adjust position in line with rings so that wirings are in correct position
			normalise(mpos);
			rotors[middle].setPosition(mpos);
			rotors[left].setPosition(initialPositions[left]); //also reset left position as it may have changed on last encrypt
			std::vector<int> result = this->encryptWord(ciphertext);
			float score = analyser->score(result);
			if (score > max.score) {
				max = { {r,m},score }; //change the max settings and discard any that are not the highest found
			}
		}
	}
	rotors[right].setRing(max.rings[0]); //set rings
	rotors[middle].setRing(max.rings[1]);
	initialPositions[right] = initialPositions[right] + max.rings[0] - 1; //adjust positions in line with rings
	normalise(initialPositions[right]);
	initialPositions[middle] = initialPositions[middle] + max.rings[1] - 1; //adjust positions in line with rings
	normalise(initialPositions[middle]);
	homePosition(); //home positions so encryptword can immediately be called to get the predicted plaintext
	return max.score;
}

float SolverMachine::findBestPlugs()
{
	maxPlugs max{ plugboard,0 ,{} };
	std::set<int> used;
	for (int i = 0; i < 26; i++) {
		if (plugboard.getWiring()[i] != i + 1) { //looks for any currently installed plugs
			used.insert(i + 1); //adds them to list of plugs unusable
		}
	}
	for (int i = 0; i < 13; i++) { //at most 13 plugs can be added (though usually under 10 are used)
		bool changed = false; //flag marks if the top of the hill has been reached yet
		for (int a = 1; a < 27; a++) { //first plug
			if (used.contains(a)) continue;
			for (int b = 1; b < a; b++) { //second plug (<a WLOG)
				if (used.contains(b)) continue;
				plugboard.addPlug({ a,b }); //plugboard remembers last plug added
				for (int j = 0; j < 3; j++) {
					rotors[j].setPosition(initialPositions[j]); //home positions
				}
				std::vector<int> result = this->encryptWord(ciphertext);
				float score = analyser->score(result);
				if (score > max.score) { //if no good plugs are found at this level, previous level max will be compared, preventing worse plugs from being found
					changed = true;
					max = { plugboard,score,{a,b} }; //extend best plugboard
				}
				plugboard.removeLast();
			}
		}
		plugboard = max.plug;
		used.insert(max.newPair[0]);
		used.insert(max.newPair[1]);
		std::cout << char(max.newPair[0] + 64) << char(max.newPair[1] + 64) << " ";
		if (!changed) break; //if top of hill reached, stop looking.
	}
	homePosition(); //for encrypt word directly after
	return max.score;
}

void SolverMachine::setPosition(int N, int pos)
{
	rotors[N].setPosition(pos);
	initialPositions[N] = pos;
}

void SolverMachine::setPositions(std::array<int, 3> in)
{
	Machine::setPositions(in);
	initialPositions = in;
}

void SolverMachine::homePosition()
{
	Machine::setPositions(initialPositions);
}

maxPosition SolverMachine::findBestPositions(){
	maxPosition max = {{1,1,1},0};
	for (int li = 1; li < 27; li++){
		for (int mi = 1; mi < 27; mi++){
			for(int ri = 1; ri < 27; ri++){
				rotors[left].setPosition(li); //positions are reset every encrypt, as they will change with an encrypt
				rotors[middle].setPosition(mi);
				rotors[right].setPosition(ri);
				std::vector<int> result = encryptWord(ciphertext);
				float score = analyser->score(result);
				if ( score > max.score){
					max = {{li,mi,ri},score}; //replace max if better found
				}
			}
		}
	}
	return max;
}