//
// Created by simpl on 04-09-2020.
//
#include "../utils/shellStateDef.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#ifndef SHELL_LS_H
#define SHELL_LS_H
int ls(struct shellState *currentState, char **commandArray, int numParts);
#endif //SHELL_LS_H
