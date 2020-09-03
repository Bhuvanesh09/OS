cmake_minimum_required(VERSION 3.10)
project(shell C)

set(CMAKE_C_STANDARD 11)

add_executable(shell main.c utils/hud.c utils/hud.h utils/shellStateDef.c utils/shellStateDef.h utils/inputHandler.c utils/inputHandler.h)
target_link_libraries(shell m)