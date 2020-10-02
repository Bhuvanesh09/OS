//
// Created by simpl on 03-09-2020.
//

#ifndef SHELL_COMMANDHANDLER_H
#define SHELL_COMMANDHANDLER_H
#include "utils/shellStateDef.h"
#include "commands/cd.h"
#include "commands/echo.h"
#include "commands/ls.h"
#include "commands/generalCommand.h"
#include <stdlib.h>
int handleCommand(struct shellState *currentShellState, char **commandArray, int numParts, char *rawCommand);
#endif //SHELL_COMMANDHANDLER_H
