#include<unistd.h>
#include<stdio.h>
#include<stdio.h> 
#include<fcntl.h> 
#include<errno.h>
#include<string.h>
#include<sys/stat.h>

int main(int argc, char *argv[]){
    printf("%d, %s", argc, argv[1]);
}