//
// Created by simpl on 03-09-2020.
//

#include "echo.h"

int echo(struct shellState * state, char **commandArray, int numParts, char *rawCommand) {
    char delim[] = " \t\n";
    char *stringCopy = (char *)malloc(sizeof(char)*1000);
    strcpy(stringCopy, rawCommand);
    char *part = strtok(stringCopy, delim);
    part = strtok(NULL, delim);
    dprintf(1, "%s", rawCommand + (part-stringCopy));
    return 0;
}