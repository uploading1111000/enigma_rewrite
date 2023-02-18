include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)
add_library(wirings wirings.cpp)
add_library(rotorSpecification rotorSpecification.cpp )
target_link_libraries(rotorSpecification PUBLIC wirings)
add_library(rotor rotor.cpp)
target_link_libraries(rotor PUBLIC
		wirings
		rotorSpecification
)
add_library(machineSpecification machineSpecification.cpp)
target_link_libraries(machineSpecification PUBLIC
		wirings
		rotorSpecification
		nlohmann_json::nlohmann_json
)
add_library(machineSpecificationFour machineSpecification4.cpp)
target_link_libraries(machineSpecificationFour PUBLIC
		wirings
		rotorSpecification
		machineSpecification
		nlohmann_json::nlohmann_json
)
add_library(machine machine.cpp)
target_link_libraries(machine PUBLIC
		machineSpecification
		rotor
		wirings
)