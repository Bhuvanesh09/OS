#include <stdlib.h>
#include "utils/shellStateDef.h"
#include "utils/inputHandler.h"
#include "commandHandler.h"
int main() {
    struct shellState *currentShellState = (struct shellState*) malloc(sizeof(struct shellState));
    char *currentCommand = (char *) malloc(sizeof(char) * 100);
    char **commandPartArray = (char *)malloc(sizeof(int) * 100);
    setHomePath(currentShellState);
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while(1) {
        updateShellState(currentShellState);
        printShellState(currentShellState);
        updateCommand(currentCommand);
        if(strcmp(currentCommand, "\n") == 0) continue;
        int commandPartSize = splitStringOnSpaces(currentCommand, commandPartArray);
        handleCommand(currentShellState, commandPartArray, commandPartSize, currentCommand);
    }
#pragma clang diagnostic pop
    return 0;
}
