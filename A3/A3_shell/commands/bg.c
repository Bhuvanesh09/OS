//
// Created by simpl on 29-09-2020.
//

#include "bg.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
int bg(struct shellState *currentState, char **commandArray, int numParts){
    if(numParts != 2){
        dprintf(1, "Please enter just one argument of job id. \n");
        return 1;
    }

    int index = strtol(commandArray[1], NULL, 10);

    if(index >= currentState->jobIndex){
        dprintf(1, "Sorry, the job ID doesn't exist. \n");
        return 1;
    }
    char *processStatFile = (char *) malloc(sizeof(char) * 1000);
    sprintf(processStatFile, "/proc/%d/stat", currentState->jobRecord[index].processId);
    FILE *fileObject = fopen(processStatFile, "r");
    if(!fileObject){
        dprintf(1, "Sorry, the job ID doesn't exist. \n");
        return 1;
    }


    pid_t pid = currentState->jobRecord[index].processId;

    int stat;

    kill(pid, SIGCONT);//continue the stopped process
    dprintf(1, "Now the process %s with pid = %d is Running. :)\n", currentState->jobRecord[index].commandName, pid);
    return 0;
}
