//
// Created by simpl on 03-09-2020.
//

#ifndef SHELL_SHELLSTATEDEF_H
#define SHELL_SHELLSTATEDEF_H

struct shellState{
    char *user;
    char *hostname;
    char *currentPath;
};

void updateShellState(struct shellState *state);
void printShellState(struct shellState *state);

#endif //SHELL_SHELLSTATEDEF_H
