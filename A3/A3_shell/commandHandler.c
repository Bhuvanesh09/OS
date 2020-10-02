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

int handleCommand(struct shellState *currentShellState, char *commandArray[], int numParts, char *rawCommand){
    if(redirectionPresent(commandArray, numParts)){
        return resolveRedirection(currentShellState, commandArray, numParts);
    }
    if(strcmp(commandArray[0],"cd")==0){
        return cd( currentShellState, commandArray, numParts);
    }
    else if(strcmp(commandArray[0],"exit")== 0) exit(0);
    else if(strcmp(commandArray[0],"quit")== 0) exit(0);
    else if(strcmp(commandArray[0],"pwd") == 0) {
        printf("%s\n", currentShellState->currentPath);
        return 1;
    }
    else if(strcmp(commandArray[0], "jobs") == 0) {
        return jobs(currentShellState);
    }
    else if(strcmp(commandArray[0], "bg") == 0) {
        return bg(currentShellState, commandArray, numParts);
    }
    else if(strcmp(commandArray[0], "fg") == 0) {
        return fg(currentShellState, commandArray, numParts);
    }
    else if(strcmp(commandArray[0], "overkill") == 0) {
        return overkill(currentShellState);
    }
    else if(strcmp(commandArray[0], "kjob") == 0) {
        return kjob(currentShellState, commandArray, numParts);
    }
    else if(strcmp(commandArray[0], "echo") == 0) {
        return echo(currentShellState, commandArray, numParts, rawCommand);
    }
    else if(strcmp(commandArray[0], "ls") == 0){
        return ls(currentShellState, commandArray, numParts);
    }
    else if(strcmp(commandArray[0],"pinfo") == 0){
        return pinfo(currentShellState,commandArray, numParts);
    }
    else if(strcmp(commandArray[0],"history") == 0){
        return showHistory(currentShellState, commandArray, numParts);
    }
    else if(strcmp(commandArray[0],"setenv") == 0){
        return setenvCustom(currentShellState, commandArray, numParts);
    }
    else if(strcmp(commandArray[0],"unsetenv") == 0){
        return unsetenvCustom(currentShellState, commandArray, numParts);
    }
    else{
        return executeGeneralCommand(currentShellState, commandArray, numParts);
    }
}