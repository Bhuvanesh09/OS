#include<unistd.h>
#include<stdio.h>
#include<stdio.h> 
#include<fcntl.h> 
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>

char yesOrNo[5];
char entity[10];
char permission[10];
char outText[1000];
int perms[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
long long int BATCH_SIZE = 1000000;
char errorText[1000];
char outText[1000];

void setEntity(int i){
    if(i==0) sprintf(entity,"User");
    else if(i==1) sprintf(entity, "Group");
    else if(i==2) sprintf(entity, "Others");
}
void setPermission(int i){
    if(i==0) sprintf(permission,"Read");
    else if(i==1) sprintf(permission, "Write");
    else if(i==2) sprintf(permission, "Execute");
}
void resolvePerm(struct stat fileStatus, char *fileName, int ent, int permKind){
    sprintf(yesOrNo, (fileStatus.st_mode & perms[ent*3+permKind])?"Yes":"No");
    setEntity(ent);
    setPermission(permKind);
    sprintf(outText, "%s has the %s permission on %s : %s\n", entity, permission, fileName, yesOrNo );
    write(1,outText,strlen(outText));
}
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

    for(int i=1; i<4; i++ ){//filename loop
        struct stat fileStatus;
        stat(argv[i], &fileStatus); //Setting the file status
        for(int j=0; j<3; j++){//entity loop
            for(int k=0; k<3; k++){//permission kind loop
                resolvePerm(fileStatus, argv[i], j, k);
            }
        }
    }

    if(checkFilesReverse(newFilePath, oldFilePath)){
        sprintf(outText,"\rYes they are reverse of each other. :)\n");
    }
    else{
        sprintf(outText,"\rNo they are not reverse of each other. :(\n");
    }
    write(1,outText, strlen(outText));
    return 0;


}