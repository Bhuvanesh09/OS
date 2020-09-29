//
// Created by simpl on 03-09-2020.
//

#ifndef SHELL_CD_H
#define SHELL_CD_H
#include "../utils/shellStateDef.h"
#include<unistd.h>
#include<stdio.h>
int cd(struct shellState *currentState, char **commandArray, int numParts);
#endif //SHELL_CD_H
