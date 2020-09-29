//
// Created by simpl on 03-09-2020.
//

#ifndef SHELL_INPUTHANDLER_H
#define SHELL_INPUTHANDLER_H

#include <stdlib.h>
#include <stdio.h>

void updateCommand(char *commandString);
int splitStringOnSpaces(char *string, char **parsedArray);
int splitStringOnPipes(char *string, char *parsedArray[]);
#endif //SHELL_INPUTHANDLER_H
