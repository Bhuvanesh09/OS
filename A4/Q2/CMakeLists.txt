# cmake_minimum_required(VERSION <specify CMake version here>)
project(Q2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
add_executable(Q2 main.c main.h student.c student.h zone.c zone.h pharma.c pharma.h)