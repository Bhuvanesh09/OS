//
// Created by simpl on 04-09-2020.
//

#include "ls.h"

void resolveFlags(char *option, int *flagL, int *flagA){
    for(int i=1; i<strlen(option); i++){
        if(option[i] == 'l') *flagL = 1;
        else if(option[i] == 'a') *flagA = 1;
        else perror("Invalid Options Given");
    }
    return;
}
void resolveDirectory(struct shellState *currentState, char *arg, char *directory){
    if(strcmp(arg, "~") == 0){
        strcpy(directory, currentState->homePath);
    }else {
        strcpy(directory, arg);
    }
    return;
}

void resolveDirEntry(struct dirent *dirEntry, int flagL){
    if(!flagL){
        printf("%s\n", dirEntry->d_name);
        return;
    }

    struct stat statObject;
    stat(dirEntry->d_name, &statObject);

    char *permission = (char *) malloc(sizeof(char) * 10);
    strcpy(permission, "");
    strcat(permission, statObject.st_mode & S_IRUSR ? "r" : "-");
    strcat(permission, statObject.st_mode & S_IWUSR ? "w" : "-");
    strcat(permission, statObject.st_mode & S_IXUSR ? "x" : "-");
    strcat(permission, statObject.st_mode & S_IRGRP ? "r" : "-");
    strcat(permission, statObject.st_mode & S_IWGRP ? "w" : "-");
    strcat(permission, statObject.st_mode & S_IXGRP ? "x" : "-");
    strcat(permission, statObject.st_mode & S_IROTH ? "r" : "-");
    strcat(permission, statObject.st_mode & S_IWOTH ? "w" : "-");
    strcat(permission, statObject.st_mode & S_IXOTH ? "x" : "-");

    printf("%10s %s\n", permission, dirEntry->d_name) ;
}
int ls(struct shellState *currentState, char **commandArray, int numParts){
    int flagA = 0, flagL = 0;
    char *directory = (char *) malloc(sizeof(char) * 1000);
    directory = currentState->currentPath;
    for(int i=1; i<numParts; i++){
        if(commandArray[i][0] == '-'){
            resolveFlags(commandArray[i], &flagL, &flagA);
            continue;
        }else {
            resolveDirectory(currentState, commandArray[i], directory);
        }
    }

    struct dirent *DirEntry ;
    DIR *dirInstance = opendir(directory);
    if(!dirInstance){
        printf("Shell encountered an error in opening this Directory.\n");
    }
    DirEntry = readdir(dirInstance);
    while(DirEntry){
        if(DirEntry->d_name[0] == '.' && !flagA){
            DirEntry = readdir((dirInstance));
            continue;
        }
        resolveDirEntry(DirEntry, flagL);
        DirEntry = readdir(dirInstance);
    }
    return 1;
}
