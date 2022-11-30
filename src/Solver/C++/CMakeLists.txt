cmake_minimum_required(VERSION 3.10)
project(Solver)
find_package(Python 3.6 COMPONENTS Interpreter Development REQUIRED)
add_subdirectory(pybind11)
add_library(functions funcs.cpp)
pybind11_add_module(bindings binds.cpp)
target_link_libraries(bindings PUBLIC functions)
target_include_directories(bindings PUBLIC
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_BINARY_DIR}"
)
