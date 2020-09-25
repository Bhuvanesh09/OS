//
// Created by simpl on 25-09-2020.
//

#include <unistd.h>
#include "piping.h"
#include "./inputHandler.h"
#include "../commandHandler.h"
int checkHasPiping(char **commandArray, int numParts){
   for(int i=0; i<numParts; i++){
       if(strcmp(commandArray[i], "|")==0){
           return 1;
       }
   }
   return 0;
}

void handlePiping(struct shellState *currentShellState, char *rawCommand){
    char **pipedCommands = (char *)malloc(sizeof(int) * 100);
    char **commandParts = (char *)malloc(sizeof(int) * 100);
    int numCommands = splitStringOnPipes(rawCommand, pipedCommands);
    int numParts;
    int standard_input = dup(0), standard_output = dup(1);
    int pipeObject[2];
    if(pipe(pipeObject)<0){
        perror(" Couldn't Create pipe. :( ");
        return;
    }
    if(dup2(pipeObject[1], 1)!=1) perror("Gadbad"); //writer here
    close(pipeObject[1]);
    numParts = splitStringOnSpaces(pipedCommands[0],commandParts);
    handleCommand(currentShellState, commandParts, numParts, pipedCommands[0]);
    dup2(pipeObject[0], 0); //reader here
    close(pipeObject[0]);

    for(int i=1; i<numCommands-1; i++){
        if(pipe(pipeObject)<0){
            perror(" Couldn't Create pipe. :( ");
            return;
        }
        dup2(pipeObject[1], 1);
        close(pipeObject[1]);
        numParts = splitStringOnSpaces(pipedCommands[i],commandParts);
        handleCommand(currentShellState, commandParts, numParts, pipedCommands[i]);
        dup2(pipeObject[0], 0);
        close(pipeObject[0]);
    }

    dup2(standard_output, 1);

    numParts = splitStringOnSpaces(pipedCommands[numCommands-1],commandParts);
    handleCommand(currentShellState, commandParts, numParts, pipedCommands[numCommands-1]);
    dup2(standard_input, 0);



    return;
}
