//
// Created by simpl on 03-09-2020.
//

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "shellStateDef.h"


void updateShellState( struct shellState *state){
    state->user = getenv("USER");
    state->hostname = (char*) malloc(1000 * sizeof(char) );
    state->currentPath = (char*) malloc(1000 * sizeof(char) );
    gethostname(state->hostname,1000);
    getcwd(state->currentPath, 1000);
}

void printShellState(struct  shellState *state){
    printf("<%s@%s> %s", state->user, state->hostname, state->currentPath);
    fflush(stdout);
};