//
// Created by simpl on 29-09-2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include "fg.h"
int fg(struct shellState *currentState, char **commandArray, int numParts){
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
    tcsetpgrp(0,pid); //setting the group id to current 0

    // Now have to wait as the current process it the above one returns

    waitpid(pid, &stat, WUNTRACED);
    signal(SIGTTOU, SIG_IGN); // after wait, the current process tries to write to terminal which causes error.
    tcsetpgrp(0,getpid()); //adding the current process back to the process group
    signal(SIGTTOU,SIG_DFL); // Now we need default handelling of the error ;


}
