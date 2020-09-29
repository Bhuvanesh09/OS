//
// Created by simpl on 29-09-2020.
//

#ifndef SHELL_KJOB_H
#define SHELL_KJOB_H

#include "../utils/shellStateDef.h"

int kjob(struct shellState *currentState, char **commandArray, int numParts);
int overkill(struct shellState *currentState);
#endif //SHELL_KJOB_H
