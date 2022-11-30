cmake_minimum_required(VERSION 3.10)
project(Solver)

add_subdirectory(pybind11)
pybind11_add_module(example example.cpp)
