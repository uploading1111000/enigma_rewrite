#include "wirings.h"
class Reflector : public Wirings {
public:
	char getReflectorID() {
		return char(getID() + 65);
	}
	using Wirings::Wirings;
};