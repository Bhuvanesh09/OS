//
// Created by simpl on 03-09-2020.
//

#include "commandHandler.h"

void handleCommand(struct shellState *currentShellState, char *commandArray[], int numParts, char *rawCommand){
    if(strcmp(commandArray[0],"cd")==0){
        cd( currentShellState, commandArray, numParts);
    }
    else if(strcmp(commandArray[0],"exit")== 0) exit(0);
    else if(strcmp(commandArray[0],"pwd") == 0) {
        printf("%s\n", currentShellState->currentPath);
    }
    else if(strcmp(commandArray[0], "echo") == 0) {
        echo(currentShellState, commandArray, numParts, rawCommand);
    }
    else if(strcmp(commandArray[0], "ls") == 0){
        ls(currentShellState, commandArray, numParts);
    }
    else{
        executeGeneralCommand(currentShellState, commandArray, numParts);
    }
}