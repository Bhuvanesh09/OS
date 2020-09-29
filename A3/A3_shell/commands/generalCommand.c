//
// Created by simpl on 08-09-2020.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "generalCommand.h"


char *jobIdFake[1000000];

void childExit(){
    pid_t	pid;
    int stat;
    pid = waitpid(-1,&stat, WNOHANG);
    if(pid <= 0) return;

    if(stat != 0){
        fprintf(stderr, "The process %s with pid = %d, gave a failed exit code :( ", jobIdFake[pid], pid);
    }
    else {
        fprintf(stderr, "The process %s with pid = %d ended normally. :)   ", jobIdFake[pid], pid);
    }
}
int executeGeneralCommand(struct shellState *currentState, char ** commandArray, int nparts){
    pid_t pid;
    int isBackground = 0;
    if(strcmp(commandArray[nparts-1], "&") == 0) {
        isBackground = 1;
        commandArray[nparts-1] = NULL;
    }
    signal(SIGCHLD, childExit);
    pid = fork();

    if(pid<0){

        perror("Couldn't create a child process. :(");
        return -1;
    }
   commandArray[nparts] = NULL;
   if(pid == 0) {

       setpgid(0,0); // setting the group id of the child to 0 to make vim work in bg. otherwise it takes over.
           if(execvp(commandArray[0], commandArray) < 0){
               perror("Command Doesn't exist :(");
               exit(1);
           };

       //If reaches here, it means command successful :)
       exit(0);
   }
   int index = currentState->jobIndex;
   currentState->jobRecord[index].processId = pid;
   strcpy(currentState->jobRecord[index].commandName, commandArray[0]);
   currentState -> jobIndex = index + 1;

   if(isBackground){
       //handle background
       char *name = (char *) malloc(sizeof(char) * 1000);
       strcpy(name, commandArray[0]);
       jobIdFake[pid] = name;
   }
   else {
//        while(wait(NULL) != pid) { }; //waits till the current child returns with a value.
        // instead of a loop , we can use waitpid
        int stat;
        tcsetpgrp(0, pid);
        waitpid(pid, &stat, WUNTRACED);
        signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(0, getpid());
        signal(SIGTTOU, SIG_DFL);
   }

   return 0;
}
