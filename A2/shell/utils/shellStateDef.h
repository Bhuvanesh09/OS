//
// Created by simpl on 03-09-2020.
//

#ifndef SHELL_SHELLSTATEDEF_H
#define SHELL_SHELLSTATEDEF_H
#include <string.h>

struct shellState{
    char *user;
    char *hostname;
    char *currentPath;
    char *homePath;
    char *jobList[40000];
};

void updateShellState(struct shellState *state);
void printShellState(struct shellState *state);
void setHomePath(struct shellState *state);
char *relativePath(struct shellState *state);
#endif //SHELL_SHELLSTATEDEF_H
