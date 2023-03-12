#include "wirings.h"
#pragma once
class Reflector : public Wirings {
public:
	char getReflectorID() {             
		return char(getID() + 66);
	}
	using Wirings::Wirings;
};