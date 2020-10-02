//
// Created by simpl on 08-09-2020.
//

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "pinfo.h"
int pinfo(struct shellState *currentState, char **commandArray, int numParts){
    char *processDir = (char *) malloc(sizeof(char)*1000);
    char *workingPath = (char *) malloc(sizeof(char)*1000);
    strcpy(processDir, "/proc/");
    FILE *workingFile;
    char *garbageString = (char *) malloc(sizeof(char) * 10000);
    long long int pid, retStatus;
    char *pid_string = (char *) malloc(sizeof(char)*1000);
    long long int mem;
    char *status = (char *) malloc(sizeof(char) * 1000);

    if(numParts > 1){
        strcat(processDir, commandArray[1]);
    }else {
        sprintf(processDir, "%s%d", processDir, getpid());
    }

    //Stat:

    strcpy(workingPath, processDir);
    strcat(workingPath, "/stat");

    workingFile = fopen(workingPath, "r");
    if(!workingFile) {
        perror("Couldn't gather stat info :( ");
        return 1;
    }

    fscanf(workingFile, "%lld", &pid);
    fscanf(workingFile, "%s", garbageString);
    fscanf(workingFile, "%s", status);
    status[1] = '\0';

    printf("pid -- %lld\n", pid);
    printf("Process Status -- %s\n", status);
    fclose(workingFile);

    //For memory:

    strcpy(workingPath, processDir);
    strcat(workingPath, "/statm");

    workingFile = fopen(workingPath, "r");
    if(!workingFile) perror("Couldn't gather memory info :(    ");

    fscanf(workingFile, "%lld", &mem);
    fclose(workingFile);

    printf("memory -- %lld\n", mem);

    // For executable link:
    strcpy(workingPath, processDir);
    strcat(workingPath, "/exe");

    garbageString = (char *)malloc(sizeof(char)*1000);
    retStatus = readlink(workingPath, garbageString, 1000);

    if(retStatus<0) {
        perror("Could not find the executable sorry :(    ");
        return 1;
    }

    printf("Executable Path -- %s\n", garbageString);

    return 0;
}
