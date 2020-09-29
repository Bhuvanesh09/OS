//
// Created by simpl on 03-09-2020.
//
#include "../utils/shellStateDef.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef SHELL_ECHO_H
#define SHELL_ECHO_H

int echo(struct shellState * state, char **commandArray, int numParts, char *rawCommand);
#endif //SHELL_ECHO_H
