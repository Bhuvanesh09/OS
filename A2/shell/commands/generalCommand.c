//
// Created by simpl on 08-09-2020.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "generalCommand.h"
int executeGeneralCommand(struct shellState *currentState, char ** commandArray, int nparts){
    pid_t pid;
    int forkReturn = 0;
    int isBackground = 0;
    if(strcmp(commandArray[nparts-1], "&") == 0) isBackground = 1;

    pid = fork();

    if(pid<0){
        perror("Couldn't create a child process. :(");
        return -1;
    }

   if(pid == 0) {
       if(execvp(commandArray[0], commandArray) < 0){
           perror("Command Doesn't exist :(");
           return -1;
       };

       //If reaches here, it means command successful :)
       exit(0);
   }

   if(isBackground){
       //handle background
       printf("Background apps don;t work yet");
   }
   else {
        while(wait(NULL) != pid) { }; //waits till the current child returns with a value.

   }

   return 0;
}
