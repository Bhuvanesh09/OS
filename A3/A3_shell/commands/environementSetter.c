//
// Created by simpl on 28-09-2020.
//

#include <stdlib.h>
#include <stdio.h>
#include "environementSetter.h"
int setenvCustom(struct shellState *currentShellState,char ** commandArray, int numParts){
    if(numParts > 3 || numParts == 1 ){
        dprintf(1, "Sorry, make sure there are 1 or 2 arguments to the command. \n");
        return 1;
    }
    if(numParts == 2){
        char * emptyString = (char *) malloc(1000);
        strcpy(emptyString, "");
        commandArray[2] = emptyString;
    }

    int stat = setenv(commandArray[1], commandArray[2], 1);

    if(stat!=0){
        perror("Could not set the environment sorry. ");
        return 1;
    }
    return 0;
}

int unsetenvCustom(struct shellState *currentState, char ** commandArray, int numParts){
    if(numParts > 2 || numParts == 1) {
        dprintf(1, "Sorry, make sure there is exactly 1 argument to the command. \n");
        return 1;
    }

    int stat = unsetenv(commandArray[1]);

    if(stat!=0){
        perror("Could not unset it, sorry. ");
        return 1;
    }

    return 0;
}
