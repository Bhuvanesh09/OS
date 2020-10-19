# cmake_minimum_required(VERSION <specify CMake version here>)
project(merge_sort C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
add_executable(merge_sort main.c)