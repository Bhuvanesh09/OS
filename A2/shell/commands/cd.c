//
// Created by simpl on 03-09-2020.
//

#include <stdlib.h>
#include "cd.h"

int cd(struct shellState *currentState, char **commandArray, int numParts){
    if(strcmp(commandArray[1]," ")==0 || strcmp(commandArray[1], "")==0 || strcmp(commandArray[1], ".")==0) {
        return 1;
    }else if(commandArray[1][0] == '~'){
        char *dir = (char *) malloc(sizeof(char)*1000);
        strcpy(dir, currentState->homePath);
        strcat(dir, commandArray[1]+1);
        int suc = chdir(dir);
        if(suc<0){
            perror(currentState->homePath);
            return -1;
        }
        else {
            updateShellState(currentState);
            return 1;
        }
    }else {
        int suc = chdir(commandArray[1]);
        if(suc<0) {
            perror(commandArray[1]);
            return -1;
        }else {
            updateShellState(currentState);
            return 1;
        }
    }
}
