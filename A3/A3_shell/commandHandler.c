//
// Created by simpl on 03-09-2020.
//

#include "commandHandler.h"
#include "commands/pinfo.h"
#include "commands/history.h"
#include "commands/fg.h"
#include "commands/bg.h"
#include "commands/jobs.h"
#include "commands/kjob.h"
#include "utils/redirection.h"
#include "commands/environementSetter.h"

void handleCommand(struct shellState *currentShellState, char *commandArray[], int numParts, char *rawCommand){
    if(redirectionPresent(commandArray, numParts)){
        resolveRedirection(currentShellState, commandArray, numParts);
        return;
    }
    if(strcmp(commandArray[0],"cd")==0){
        cd( currentShellState, commandArray, numParts);
    }
    else if(strcmp(commandArray[0],"exit")== 0) exit(0);
    else if(strcmp(commandArray[0],"quit")== 0) exit(0);
    else if(strcmp(commandArray[0],"pwd") == 0) {
        printf("%s\n", currentShellState->currentPath);
    }
    else if(strcmp(commandArray[0], "jobs") == 0) {
        jobs(currentShellState);
    }
    else if(strcmp(commandArray[0], "bg") == 0) {
        bg(currentShellState, commandArray, numParts);
    }
    else if(strcmp(commandArray[0], "fg") == 0) {
        fg(currentShellState, commandArray, numParts);
    }
    else if(strcmp(commandArray[0], "overkill") == 0) {
        overkill(currentShellState);
    }
    else if(strcmp(commandArray[0], "kjob") == 0) {
        kjob(currentShellState, commandArray, numParts);
    }
    else if(strcmp(commandArray[0], "echo") == 0) {
        echo(currentShellState, commandArray, numParts, rawCommand);
    }
    else if(strcmp(commandArray[0], "ls") == 0){
        ls(currentShellState, commandArray, numParts);
    }
    else if(strcmp(commandArray[0],"pinfo") == 0){
        pinfo(currentShellState,commandArray, numParts);
    }
    else if(strcmp(commandArray[0],"history") == 0){
        showHistory(currentShellState, commandArray, numParts);
    }
    else if(strcmp(commandArray[0],"setenv") == 0){
        setenvCustom(currentShellState, commandArray, numParts);
    }
    else if(strcmp(commandArray[0],"unsetenv") == 0){
        unsetenvCustom(currentShellState, commandArray, numParts);
    }
    else{
        executeGeneralCommand(currentShellState, commandArray, numParts);
    }
}