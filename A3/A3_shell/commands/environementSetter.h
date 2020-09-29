//
// Created by simpl on 28-09-2020.
//

#ifndef SHELL_ENVIRONEMENTSETTER_H
#define SHELL_ENVIRONEMENTSETTER_H

#include "../utils/shellStateDef.h"

int setenvCustom(struct shellState *currentShellState,char **commandArray, int numParts);
int unsetenvCustom(struct shellState *currentShellState,char **commandArray, int numParts);
#endif //SHELL_ENVIRONEMENTSETTER_H
