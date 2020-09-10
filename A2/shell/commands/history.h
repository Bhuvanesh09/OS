//
// Created by simpl on 10-09-2020.
//

#ifndef SHELL_HISTORY_H
#define SHELL_HISTORY_H
#include "../utils/shellStateDef.h"

FILE * makeHistoryFile(struct shellState *currentState);
int addToHistory(struct shellState *currentState, char *rawCommand);
int showHistory(struct shellState *currentState, char **commandArray, int numParts);
#endif //SHELL_HISTORY_H
