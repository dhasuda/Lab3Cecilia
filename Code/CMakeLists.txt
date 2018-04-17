cmake_minimum_required(VERSION 3.9)
project(Code)

set(CMAKE_CXX_STANDARD 11)

add_executable(Code main.cpp cmake-build-debug/CostFunction.cpp cmake-build-debug/CostFunction.h cmake-build-debug/Particle.cpp cmake-build-debug/Particle.h cmake-build-debug/Population.cpp cmake-build-debug/Population.h)