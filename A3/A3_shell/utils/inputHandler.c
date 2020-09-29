//
// Created by simpl on 03-09-2020.
//

#include <memory.h>
#include "inputHandler.h"

void updateCommand(char *commandString){
    size_t  size = 1000;
    getline(&commandString, &size, stdin);
}

int splitStringOnSpaces(char *string, char *parsedArray[]){
    // This parses the string on spaces and returns the number of things it parsed it to.
    char delim[] = " \t\n";
    char *stringCopy = (char *)malloc(sizeof(char)*1000);
    strcpy(stringCopy, string);
    char *part = strtok(stringCopy, delim);
    int numParts = 0;
    for(int i=0; part; i++){
        parsedArray[i] = part;
        part = strtok(NULL, delim);
        numParts = i+1;
    }
    return numParts;
}

int splitStringOnPipes(char *string, char *parsedArray[]){
    // This parses the string on spaces and returns the number of things it parsed it to.
    char delim[] = "|";
    char *stringCopy = (char *)malloc(sizeof(char)*1000);
    strcpy(stringCopy, string);
    char *part = strtok(stringCopy, delim);
    int numParts = 0;
    for(int i=0; part; i++){
        parsedArray[i] = part;
        part = strtok(NULL, delim);
        numParts = i+1;
    }
    return numParts;
}