cmake_minimum_required(VERSION 3.10)
project(shell C)

set(CMAKE_C_STANDARD 11)

add_executable(shell main.c utils/shellStateDef.c utils/shellStateDef.h utils/inputHandler.c utils/inputHandler.h commandHandler.c commandHandler.h commands/cd.c commands/cd.h commands/echo.c commands/echo.h commands/ls.c commands/ls.h commands/generalCommand.c commands/generalCommand.h commands/pinfo.c commands/pinfo.h commands/history.c commands/history.h utils/piping.c utils/piping.h utils/redirection.c utils/redirection.h commands/environementSetter.c commands/environementSetter.h commands/jobs.c commands/jobs.h commands/kjob.c commands/kjob.h utils/signalHandlers.c utils/signalHandlers.h commands/fg.c commands/fg.h commands/bg.c commands/bg.h)
target_link_libraries(shell m)