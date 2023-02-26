cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
project(Solver)
find_package(Python 3.6 COMPONENTS Interpreter Development REQUIRED)
set(BOOST_ROOT = "C:/Boost/boost_1_81_0")
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.81.0 REQUIRED COMPONENTS serialization)
add_subdirectory(pybind11)
add_subdirectory(simulation)
add_subdirectory(utils)
add_subdirectory(analysis)
add_executable(main debug.cpp)
pybind11_add_module(binds binds.cpp)
target_link_libraries(main PUBLIC 
        wirings
        wiringutil
        rotorSpecification
        rotor
		machineSpecification
        machineSpecificationFour
        machine
        machineFour
        IOC
        Boost::headers
        Boost::serialization
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
        "${PROJECT_SOURCE_DIR}/analysis"
        "${Boost_INCLUDE_DIR}"
)
