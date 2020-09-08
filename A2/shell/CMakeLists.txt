cmake_minimum_required(VERSION 3.10)
project(shell C)

set(CMAKE_C_STANDARD 11)

add_executable(shell main.c utils/shellStateDef.c utils/shellStateDef.h utils/inputHandler.c utils/inputHandler.h commandHandler.c commandHandler.h commands/cd.c commands/cd.h commands/echo.c commands/echo.h commands/ls.c commands/ls.h commands/generalCommand.c commands/generalCommand.h)
target_link_libraries(shell m)