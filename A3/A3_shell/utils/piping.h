//
// Created by simpl on 25-09-2020.
//

#ifndef SHELL_PIPING_H
#define SHELL_PIPING_H

#include "./shellStateDef.h"
#include "./inputHandler.h"

int checkHasPiping(char **commandArray, int numParts);
void handlePiping(struct shellState *currentShellState,  char *rawCommand);

#endif //SHELL_PIPING_H
