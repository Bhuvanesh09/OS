//
// Created by simpl on 25-09-2020.
//

#ifndef SHELL_REDIRECTION_H
#define SHELL_REDIRECTION_H

#include "./inputHandler.h"
#include "./shellStateDef.h"

int redirectionPresent(char **commandArray, int numParts);
int resolveRedirection(struct shellState *currentState, char **commandArray, int numParts);

#endif //SHELL_REDIRECTION_H
