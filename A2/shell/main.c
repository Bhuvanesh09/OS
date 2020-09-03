#include <stdlib.h>
#include "utils/shellStateDef.h"
#include "utils/inputHandler.h"
int main() {
    struct shellState *currentShellState = (struct shellState*) malloc(sizeof(struct shellState));
    char *currentCommand = (char *) malloc(sizeof(char) * 100);
    char *commandPartArray[100];
    updateShellState(currentShellState);
    printShellState(currentShellState);
    updateCommand(currentCommand);
    int commandPartSize = splitStringOnSpaces(currentCommand, commandPartArray);
    for(int i=0;i<commandPartSize;i++){
        printf("%s\n",commandPartArray[i] );
    }
    return 0;
}
