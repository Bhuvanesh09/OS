//
// Created by simpl on 29-09-2020.
//

#include <stdlib.h>
#include <stdio.h>
#include "jobs.h"

int jobs(struct shellState* currentState){
    char *processStatFile = (char *) malloc(sizeof(char) * 1000);
    char *garbageString = (char *) malloc(sizeof(char) * 1000);
    char *stat = (char *) malloc( 10);
    char *runOrStop = (char *) malloc(1000);
    for(int i=0; i < currentState->jobIndex; i++){
       sprintf(processStatFile, "/proc/%d/stat", currentState->jobRecord[i].processId);
       FILE *fileObject = fopen(processStatFile, "r");
        if(!fileObject) continue;

        fscanf(fileObject, "%s", garbageString);
        fscanf(fileObject, "%s", garbageString);
        fscanf(fileObject, "%s", stat);

        strcpy(runOrStop, strcmp(stat, "T")==0 ? "Stopped" : "Running");

        dprintf(1, "[%d] %s %s [%d]\n", i,runOrStop, currentState->jobRecord[i].commandName, currentState->jobRecord[i].processId);
    }
    return 0;
}