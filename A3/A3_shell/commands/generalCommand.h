//
// Created by simpl on 08-09-2020.
//

#ifndef SHELL_GENERALCOMMAND_H
#define SHELL_GENERALCOMMAND_H
#include "../utils/shellStateDef.h"
int executeGeneralCommand(struct shellState *currentState, char ** commandArray, int nparts);
#endif //SHELL_GENERALCOMMAND_H
