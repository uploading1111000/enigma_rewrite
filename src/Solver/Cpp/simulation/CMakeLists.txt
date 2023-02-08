add_library(wirings wirings.cpp)
add_library(rotorSpecification rotorSpecification.cpp )
target_link_libraries(rotorSpecification PUBLIC wirings)
add_library(rotor rotor.cpp)
target_link_libraries(rotor PUBLIC
		wirings
		rotorSpecification
)