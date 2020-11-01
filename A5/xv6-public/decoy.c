//
// Created by simpl on 01-11-2020.
//
// Credits : This testing function has been borrowed with permission from Animesh Sinha
#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
        int x = 0;
        for (int i = 0; i < 100000000; i++) x = x+1 % 10000;
        printf(1, "I/O section 1 running, \n", x);
        for (int i = 0; i < 100000000; i++) x = x+1 % 10000;
        printf(1, "I/O section 2 running, \n", x);
        for (int i = 0; i < 100000000; i++) x = x+1 % 10000;
        printf(1, "I/O section 3 running, \n", x);
        exit();
}