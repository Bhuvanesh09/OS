#include <stdlib.h>
#include <signal.h>
#include "utils/shellStateDef.h"
#include "utils/inputHandler.h"
#include "commandHandler.h"
#include "commands/history.h"
#include "utils/signalHandlers.h"
#include "utils/piping.h"

int main() {
    signal(SIGINT, decoyFunc);
    signal(SIGTSTP, decoyFunc);
    struct shellState *currentShellState = (struct shellState*) malloc(sizeof(struct shellState));
    currentShellState->jobIndex = 0;
    int lastStat = -10;
    setHomePath(currentShellState);
    currentShellState->lastPath = currentShellState->homePath;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while(1) {
        updateShellState(currentShellState);
        printShellState(currentShellState, lastStat);
        lastStat = -10;
        char *currentCommand = (char *) malloc(sizeof(char) * 100);
        char **commandPartArray = (char *)malloc(sizeof(int) * 100);
        updateCommand(currentCommand);
        if(strcmp(currentCommand, "\n") == 0) continue;
        addToHistory(currentShellState, currentCommand);
        int commandPartSize = splitStringOnSpaces(currentCommand, commandPartArray);
        if(checkHasPiping(commandPartArray, commandPartSize)){
            handlePiping(currentShellState, currentCommand);
        }
        else lastStat = handleCommand(currentShellState, commandPartArray, commandPartSize, currentCommand);

    }
#pragma clang diagnostic pop
    return 0;
}
