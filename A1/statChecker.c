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
void resolvePerm(struct stat fileStatus, int ent, int permKind){
    sprintf(yesOrNo, (fileStatus.st_mode & perms[ent*3+permKind])?"Yes":"No");
    setEntity(ent);
    setPermission(permKind);
    sprintf(outText, "%s has the %s permission: %s\n", entity, permission, yesOrNo );
    write(1,outText,strlen(outText));
}
int main(){
    struct stat fileStatus;
    stat("Assignment", &fileStatus);
    for(int i=0; i<3 ; i++){
        for(int j=0; j<3 ; j++){
            resolvePerm(fileStatus,i,j);
        }
    }
    return 0;
}