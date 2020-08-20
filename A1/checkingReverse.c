#include<unistd.h>
#include<stdio.h>
#include<stdio.h> 
#include<fcntl.h> 
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>

long long int BATCH_SIZE = 1000000;
char errorText[1000];
char outText[1000];
void checkIfPresent(char *path){
    if( access(path, F_OK) != -1){
        sprintf(outText, "Yes, %s is present. \n", path);
        write(1, outText, strlen(outText));
    }
    else {
        sprintf(errorText, "Error: %s is not present", path);
        perror(errorText);
        exit(1);
    }
}

int checkStringReverse(char *str1, char *str2, long long int size){
    for(long long int i=0; i<size; i++){
        if(str1[i] != str2[size-i-1]) return 0;
    }

    return 1;
}
int checkFilesReverse(char *path1, char *path2){
    int file1 = open(path1,O_RDONLY);
    int file2 = open(path2,O_RDONLY);
    char string1[BATCH_SIZE+1];
    char string2[BATCH_SIZE+1];
    long long int totalChars = lseek(file1, 0, SEEK_END);

    if(totalChars != lseek(file2, 0, SEEK_END)){
        return 0;
    }

    int flag = 0;
    long long int currentOffset = 0;
    while(!flag){
        if(currentOffset + BATCH_SIZE >= totalChars){
            lseek(file1, currentOffset, SEEK_SET);
            int R1 = read(file1,string1,totalChars-currentOffset);
            lseek(file2,-totalChars, SEEK_END);
            int R2 = read(file2, string2, totalChars-currentOffset);

            // printf("\n%d %d %lld", R1, R2, totalChars-currentOffset);
            return checkStringReverse(string1, string2, totalChars-currentOffset);
        }

        lseek(file1, currentOffset, SEEK_SET);
        read(file1, string1, BATCH_SIZE);
        lseek(file2, -(currentOffset + BATCH_SIZE), SEEK_END);
        read(file2, string2, BATCH_SIZE);

        currentOffset += BATCH_SIZE;
        float perc = currentOffset*100/totalChars;
        sprintf(outText, "\rPercent Done: %5.2f %%",perc) ;
        write(1,outText,strlen(outText));
        if(!checkStringReverse(string1, string2, BATCH_SIZE)) return 0;
        else continue;

    }

    return 1;
}
int main(int argc, char *argv[]){
    if(argc < 4){
        perror("Please provide 3 paths: <newFile> <oldFile> <directory>");
        exit(1);
    }
    
    for(int i=1; i<=3; i++){
        checkIfPresent(argv[i]);
    }
    char *newFilePath = argv[1] ;
    char *oldFilePath = argv[2] ; 
    char *directoryPath = argv[3];

    if(checkFilesReverse(newFilePath, oldFilePath)){
        sprintf(outText,"\rYes they are reverse of each other. :)\n");
    }
    else{
        sprintf(outText,"\rNo they are not reverse of each other. :(\n");
    }
    write(1,outText, strlen(outText));
    return 0;

}