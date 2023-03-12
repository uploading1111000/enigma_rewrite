add_library(solverMachine solverMachine.cpp)
target_link_libraries(solverMachine PUBLIC
	machine
	wiringutil
)
add_library(solverMachineFour solverMachine4.cpp)
target_link_libraries(solverMachineFour PUBLIC
	machineFour
	wiringutil
	solverMachine
)