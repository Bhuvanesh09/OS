#include<unistd.h>
#include<stdio.h>
#include<stdio.h> 
#include<fcntl.h> 
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
const int BATCH_SIZE = 1000000;
char outputtext[1000];


void writeToFile(int fd, char *stringToWrite, int length){
    write(fd, stringToWrite, length);
}

void reverseString(char *stringPointer, int length){
    int start=0, end = length-1;
    while(start < end){
        //interchanging them:
        stringPointer[start] ^= stringPointer[end];
        stringPointer[end] ^= stringPointer[start];
        stringPointer[start] ^= stringPointer[end];

        start += 1;
        end -= 1;
    }
}

int parseFileNameFromPath(char *string){
    int starts = strlen(string) - 1;
    for(int i=strlen(string)-1; (char)string[i] !='/' && i>=0; i--){
        starts = i;
    }
    return starts;
}

int main(int argc, char *argv[]) {
    char string[BATCH_SIZE+10];
    char outFilePath[10000] = "Assignment/";
    if(argc < 2){
        perror("Please Provide path to the file.");
        exit(1);
    }

    int makingDir = mkdir("Assignment",S_IRUSR | S_IWUSR | S_IXUSR);
    if(makingDir != 0){
        perror("Checking Directory");
    }
    int fileNamelocInPath = parseFileNameFromPath(argv[1]);
    strcat(outFilePath, argv[1] + fileNamelocInPath);
    write(1,outFilePath, strlen(outFilePath));
    write(1,"\n",1);
    int inFile, outFile;
    inFile = open(argv[1], O_RDONLY);
    outFile = open(outFilePath, O_WRONLY|O_CREAT, S_IRUSR | S_IWUSR);
    long long int totalChars = lseek(inFile, 0, SEEK_END);
    long long int lastOffset = totalChars;
    long long int currentOffset = totalChars - BATCH_SIZE;
    lseek(inFile, 0, SEEK_SET); //Placing the off_set at the beginning of the file again
    int flag = 0;
    while(!flag){
        if(currentOffset <= 0) {
           flag = 1;
           currentOffset = 0;
        }  
        lseek(inFile,currentOffset, SEEK_SET);
        int numRead = read(inFile, string, lastOffset - currentOffset);
        reverseString(string,numRead);
        writeToFile(outFile,string, numRead);
        float perc = ((totalChars - currentOffset) * 100)/totalChars;
        sprintf(outputtext, "\rPercentage Done: %6.2f %%", perc);
        write(1, outputtext, strlen(outputtext));
        lastOffset = currentOffset;
        currentOffset -= BATCH_SIZE;
    }
}