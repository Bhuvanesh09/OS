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
void setHomePath(struct shellState *state){
    state->homePath = (char*) malloc(1000 * sizeof(char));
    getcwd(state->homePath, 1000);
}

void printShellState(struct  shellState *state){
    printf("<%s@%s:%s >", state->user, state->hostname, relativePath(state));
    fflush(stdout);
};

char *relativePath(struct shellState *state){
    char *pathToshow = (char*) malloc(sizeof(char)*1000);
    strcpy(pathToshow,"~");
    int flag = 1;
    for(int i=0; i< strlen(state->homePath); i++){
        if(state->currentPath[i] != state->homePath[i]){
            flag = 0;
            break;
        }
    }
    if(flag) {
        strcpy(pathToshow + 1, state->currentPath + strlen(state->homePath));
    }else {
        strcpy(pathToshow, state->currentPath);
    }

    return pathToshow;
}