//
// Created by simpl on 01-11-2020.
//
#include "types.h"
#include "user.h"

int main(int argc, char * argv[]){
    int childProcId = fork();
    if(childProcId == 0){
        exec(argv[1], argv + 1);
    }else {
        int wtime, rtime;
        waitx(&wtime, &rtime);

        printf(1, "\nWaiting time : %d and Running Time: %d . \n", wtime, rtime);
    }
    return 0;
}