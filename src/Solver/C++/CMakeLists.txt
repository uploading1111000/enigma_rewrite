cmake_minimum_required(VERSION 3.10)
project(Solver)
find_package(Python 3.6 COMPONENTS Interpreter Development REQUIRED)
add_subdirectory(pybind11)
add_library(functions funcs.cpp)
add_executable(main debug.cpp)
pybind11_add_module(binds binds.cpp)
target_link_libraries(binds PUBLIC functions)
target_link_libraries(main PUBLIC functions)
target_include_directories(binds PUBLIC
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_BINARY_DIR}"
)
target_include_directories(main PUBLIC
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_BINARY_DIR}"
)
