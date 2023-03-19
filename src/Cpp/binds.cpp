#include "machineSpecification.h"
#include "machineSpecification4.h"
#include "machine.h"
#include "machine4.h"
#include "solverMachine.h"
#include "solverMachine4.h"
#include <boost/python.hpp>

char const* greet()
{
	return "hello, world";
}

BOOST_PYTHON_MODULE(binds)
{
	using namespace boost::python;
	def("greet", greet);
}