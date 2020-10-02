//
// Created by simpl on 25-09-2020.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <wait.h>
#include "redirection.h"
int redirectionPresent(char **commandArray, int numParts){

    for (int i=0; i<numParts; i++){
        if(strcmp(commandArray[i], ">") == 0 || strcmp(commandArray[i], "<")==0 || strcmp(commandArray[i], ">>")==0) return 1;
    }

    return 0;
}

int resolveRedirection(struct shellState *currentState, char **commandArray, int numParts){
    int writeToFile = 0, appendToFile = 0, inputFromFile = 0, fileObjectIn, fileObjectOut;
    char *outFile = (char *) malloc(sizeof(char) * 1000);
    char *inFile = (char *) malloc(sizeof(char) * 1000);
    for(int i=0; i<numParts-1; i++){
        if(commandArray[i] != NULL && strcmp(commandArray[i], ">>")==0) {
            appendToFile = 1;
            commandArray[i] = NULL;
            strcpy(outFile, commandArray[i+1]);
        }
        if(commandArray[i] != NULL && strcmp(commandArray[i], ">")==0) {
            writeToFile = 1;
            commandArray[i] = NULL;
            strcpy(outFile, commandArray[i+1]);
        }
        if(commandArray[i] != NULL && strcmp(commandArray[i], "<")==0) {
            inputFromFile = 1;
            commandArray[i] = NULL;
            strcpy(inFile, commandArray[i+1]);
        }
    }

    if(appendToFile && writeToFile) {
        fprintf(stderr, "Can't do both append and write.");
    }
    int standard_output, standard_input;

    if(writeToFile || appendToFile){
        standard_output = dup(1);
        int trOrApp = writeToFile ? O_TRUNC : O_APPEND;
       fileObjectOut = open(outFile,O_WRONLY | O_CREAT | trOrApp,  0644);
       if(fileObjectOut < 0) {
           perror("Output file error; ");
           return 1;
       }
       dup2(fileObjectOut, 1);
    }
    if(inputFromFile){
        standard_input = dup(0);
        fileObjectIn = open(inFile,O_RDONLY, 0644);
        if(fileObjectIn < 0) {
            perror("Input file error; ");
            return 1;
        }
        dup2(fileObjectIn, 0);
    }

    pid_t pid;

    pid = fork();

    if(pid==0){

        commandArray[numParts] = NULL;
        if (execvp(commandArray[0], commandArray) < 0) exit(1);
        exit(0);
    } else {
        int stat ;
        wait(&stat);
        //restoring input output:
        if(writeToFile || appendToFile) dup2(standard_output, 1);
        if(inputFromFile) dup2(standard_input, 0);
        if(stat != 0) perror("Some Error occured");
        return stat;

    }

}

