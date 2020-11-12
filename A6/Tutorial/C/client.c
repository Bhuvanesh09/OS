// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include<unistd.h>
#include<stdio.h>
#include<stdio.h> 
#include<fcntl.h> 
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8000
#define MSG_SIZE 1000
struct packet{
    char *fileName;
    int offset;
    char data[MSG_SIZE];
    int totalSize;
};

struct reqPack{
    char *fileName;
    int offset;
    int req;
    int ack;
};
void requestFile(int sock, const char *fileName){
    int valread;
    char *temp = (char *) malloc(MSG_SIZE * sizeof(char));
    struct packet *curPack = (struct packet *)malloc(sizeof(struct packet));
    struct reqPack *req = (struct reqPack *) malloc(sizeof(struct reqPack));
    req->fileName = fileName;
    req->offset = 0;
    req->req = 1;

    bzero(temp, MSG_SIZE);
    strcpy(temp, fileName);
    send(sock , temp ,MSG_SIZE, 0 );  // send the message.
    
    printf("Requested for file %s from server.\n",fileName);

    read(sock, temp, MSG_SIZE);

    long long int totalChars = strtoll(temp, NULL, 10), offset = 0;
    printf("Size of file to be copied: %lld \n", totalChars);
    int outFile = open(fileName, O_WRONLY|O_CREAT, S_IRUSR | S_IWUSR);

    while(offset < totalChars){
        bzero(temp, MSG_SIZE);
        read(sock, temp, MSG_SIZE);

        write(outFile, temp, MSG_SIZE < totalChars - offset ? MSG_SIZE : totalChars - offset);
        printf("\rDownloaded file %s : %f %%", fileName, (float) offset/totalChars);
        offset += MSG_SIZE;
    }
    printf("\n");
}
int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr)); // to make sure the struct is empty. Essentially sets sin_zero as 0
                                                // which is meant to be, and rest is defined below

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Converts an IP address in numbers-and-dots notation into either a 
    // struct in_addr or a struct in6_addr depending on whether you specify AF_INET or AF_INET6.
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)  // connect to the server address
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    requestFile(sock, argv[1]);
    return 0;
}