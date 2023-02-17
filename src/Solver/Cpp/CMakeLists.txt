cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
project(Solver)
find_package(Python 3.6 COMPONENTS Interpreter Development REQUIRED)
add_subdirectory(pybind11)
add_subdirectory(simulation)
add_subdirectory(utils)
add_executable(main debug.cpp)
pybind11_add_module(binds binds.cpp)
target_link_libraries(main PUBLIC 
        wirings
        wiringutil
        rotorSpecification
        rotor
		machineSpecification
        machineSpecificationFour
)
target_link_libraries(binds PUBLIC wirings)
target_include_directories(binds PUBLIC
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/simulation"
)
target_include_directories(main PUBLIC
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/simulation"
        "${PROJECT_SOURCE_DIR}/utils"
)
