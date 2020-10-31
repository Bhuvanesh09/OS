//
// Created by simpl on 01-11-2020.
//
#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {

    int oldValue = setPriority(atoi(argv[1]), atoi(argv[2]));
    printf(1, "Old Priority for process %s: %d \n", argv[2], oldValue);
    return oldValue;
}
