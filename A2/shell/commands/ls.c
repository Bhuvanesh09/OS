//
// Created by simpl on 04-09-2020.
//

#include <time.h>
#include "ls.h"
char * getUsername(uid_t userId){
    struct passwd *pws;
    pws = getpwuid(userId);
    if(!pws){
        char *tempStr = (char *) malloc(sizeof(char) * 100);
        sprintf(tempStr, "%d", userId);
        return tempStr;
    }
    return pws->pw_name;
}
char * getGroupName(gid_t groupId){
    struct group *grp;
    grp = getgrgid(groupId);
    if(!grp){
        char *tempStr = (char *) malloc(sizeof(char) * 100);
        sprintf(tempStr, "%d", groupId);
        return tempStr;
    }
    return grp->gr_name;
}
void resolveFlags(char *option, int *flagL, int *flagA){
    for(int i=1; i<strlen(option); i++){
        if(option[i] == 'l') *flagL = 1;
        else if(option[i] == 'a') *flagA = 1;
        else perror("Invalid Options Given");
    }
    return;
}
void resolveDirectory(struct shellState *currentState, char *arg, char *directory, int flagA, int flagL){
    if(strcmp(arg, "~") == 0){
        strcpy(directory, currentState->homePath);
    }else {
        strcpy(directory, arg);
    }


    struct dirent *DirEntry ;
    DIR *dirInstance = opendir(directory);
    if(dirInstance == NULL){
        perror(directory);
        return -1;
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

    char *timeMod = ctime(&statObject.st_mtime);
    timeMod[strlen(timeMod) - 1] = ' ';
    timeMod += 4;
    printf("%10s %d %s %s %s %s\n", permission, (int)statObject.st_nlink, getUsername(statObject.st_uid), getGroupName(statObject.st_gid),timeMod,  dirEntry->d_name) ;
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
//            resolveDirectory(currentState, commandArray[i], directory);
        }
    }
    int displayedOrNot = 0;
    for(int i=1; i<numParts; i++){
        if(commandArray[i][0] == '-'){
//            resolveFlags(commandArray[i], &flagL, &flagA);
            continue;
        }else {
            displayedOrNot = 1;
            resolveDirectory(currentState, commandArray[i], directory, flagA, flagL);
        }
    }

    if (!displayedOrNot) resolveDirectory(currentState, currentState->currentPath, directory,flagA, flagL);

   return 1;
}
