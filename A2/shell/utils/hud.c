//
// Created by simpl on 02-09-2020.
//
#include "hud.h"

void prepareForCommand(char *user, char *hostname, char *path){
    printf("<%s@%s> %s", user, hostname, path);
}