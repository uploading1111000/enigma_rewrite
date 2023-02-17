#include "wirings.h"
#pragma once
class Reflector : public Wirings {
public:
	char getReflectorID() {             //very simple
		return char(getID() + 65);
	}
	using Wirings::Wirings;
};