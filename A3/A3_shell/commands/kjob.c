//
// Created by simpl on 29-09-2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "kjob.h"
int kjob(struct shellState *currentState, char **commandArray, int numParts){
    if(numParts != 3){
        dprintf(1, "There should be 2 arguments sorry, \n ");
        return 1;
    }

    char *processStatFile = (char *) malloc(sizeof(char) * 1000);
    int jobId = atoi(commandArray[1]);
    if(jobId >= currentState->jobIndex){
        dprintf(1, "Sorry, that job id doesn't exist. \n");
        return 1;
    }

    sprintf(processStatFile, "/proc/%d/stat", currentState->jobRecord[jobId].processId);
    FILE *fileObject = fopen(processStatFile, "r");
    if(!fileObject) {
        dprintf(1, "Sorry, that job id doesn't exist. \n");
        return 1;
    };
    int signalNum = atoi(commandArray[2]);
    int stat = kill(currentState->jobRecord[jobId].processId, signalNum);
    if(stat<0){
        perror("There could be an error that was caused. :( \n");
        return 1;
    }
    return 0;
}
