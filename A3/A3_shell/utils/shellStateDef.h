//
// Created by simpl on 03-09-2020.
//

#ifndef SHELL_SHELLSTATEDEF_H
#define SHELL_SHELLSTATEDEF_H
#include <string.h>

struct job{
    int stat;
    int processId;
    char commandName[1000];
};

struct shellState{
    char *user;
    char *hostname;
    char *currentPath;
    char *lastPath;
    char *homePath;
    int jobIndex ;
    struct job jobRecord[1000];
};


void updateShellState(struct shellState *state);
void printShellState(struct shellState *state, int lastStat);
void setHomePath(struct shellState *state);
char *relativePath(struct shellState *state);
#endif //SHELL_SHELLSTATEDEF_H
