//
// Created by simpl on 10-09-2020.
//

#include <stdlib.h>
#include <stdio.h>
#include "history.h"

char previousCommands[25][1000];

int readFile(FILE *fileInstance){
    fseek(fileInstance,0, SEEK_SET);
    int numRead = 0;
    int stat = 1;
    size_t size = 1000;
    char *readLine = (char *) malloc(sizeof(char)*1000);
    for(;stat != -1;numRead++){
        stat = getline(&readLine,&size, fileInstance);
        if(stat == -1) break;
        strcpy(previousCommands[numRead], readLine);
    }
    fclose(fileInstance);
    return numRead;
}

int writeFile(int numRecords, struct shellState *currentState){
    char *fileName = (char *) malloc(sizeof(char)*10000);
    strcpy(fileName, currentState->homePath);
    strcat(fileName, "/historyRecord");

    FILE *fileInstance = fopen(fileName, "w");

    for(int i=0; i<numRecords; i++){
        fprintf(fileInstance, "%s", previousCommands[i]);
    }
    fclose(fileInstance);
}
FILE *makeHistoryFile(struct shellState *currentState){
    char *fileName = (char *) malloc(sizeof(char)*10000);
    strcpy(fileName, currentState->homePath);
    strcat(fileName, "/historyRecord");

    FILE *fileInstance = fopen(fileName, "r");

    if(fileInstance == NULL){
        fileInstance = fopen(fileName, "w");
        fprintf(fileInstance, "0\n");
    }
    if (fileInstance == NULL) {
        perror("History file Not Created. :(    ");
        return NULL;
    }
    return fileInstance;
}

int addToHistory(struct shellState *currentState, char *rawCommand){
    FILE *fileInstance = makeHistoryFile(currentState);

    int numStored = readFile(fileInstance);

    numStored = numStored < 20 ? numStored : 20;

    for(int i=numStored-1; i>=0; i--) strcpy(previousCommands[i+1], previousCommands[i]);
    strcpy(previousCommands[0], rawCommand);

    writeFile(numStored+1 < 20 ? numStored+1: 20, currentState);
    return 0;
}

int showHistory(struct shellState *currentState, char **commandArray, int numParts){
    FILE *fileInstance = makeHistoryFile(currentState);
    int numStored = readFile(fileInstance);

    int toDisplay=10;
    if(numParts > 1){
        toDisplay = atoi(commandArray[1]);
    }
    toDisplay = numStored < toDisplay ? numStored : toDisplay;

    for(int i=toDisplay-1; i>=0 ; i--){
        fprintf(stdout, previousCommands[i]);
    }
    return 0;
}
