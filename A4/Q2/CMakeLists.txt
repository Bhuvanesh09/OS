# cmake_minimum_required(VERSION <specify CMake version here>)
project(Q2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Q2 main.c cmake-build-debug/main.h main.h)