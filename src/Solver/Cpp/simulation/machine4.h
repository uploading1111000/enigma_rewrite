#include "machine.h"
#include "machineSpecification4.h"
class MachineFour : public Machine {
private:
	std::unique_ptr<MachineSpecificationFour> specification;
protected:
	Rotor rotor4;
public:
	MachineFour(MachineSpecificationFour&, std::array<int, 3>, int, int, std::vector<std::array<char, 2>>);
};