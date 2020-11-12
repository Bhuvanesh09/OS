#include <stdio.h>
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
void sendFile(int socket, char * fileName ){
    //check if file exits:
    struct packet *pac = (struct packet *) malloc(sizeof(struct packet));
    int inFile = open(fileName, O_RDONLY);

    long long int offset = 0;
    long long int numRead;
    int totalChars = lseek(inFile, 0, SEEK_END);

    //Sending the size:
    char *temp = (char *) malloc(sizeof(char) * MSG_SIZE);
    bzero(temp, MSG_SIZE);
    sprintf(temp, "%lld", totalChars);
    printf("Sending File Size : %s \n", temp);
    send(socket, temp, MSG_SIZE, 0);
    while(offset < totalChars){
        lseek(inFile, offset, SEEK_SET);
        bzero(temp, MSG_SIZE);
        read(inFile, temp, MSG_SIZE);
        send(socket, temp, MSG_SIZE, 0);
        offset += MSG_SIZE;
        printf("\rFile %s done %f %% percentage ", fileName, (float)offset * 100/totalChars );
    }
    printf("\n");
}
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;  
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)  // creates socket, SOCK_STREAM is for TCP. SOCK_DGRAM for UDP
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // This is to lose the pesky "Address already in use" error message
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt))) // SOL_SOCKET is the socket layer itself
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    printf("SOCKET CREATION SUCCESSFUL\n");
    address.sin_family = AF_INET;  // Address family. For IPv6, it's AF_INET6. 29 others exist like AF_UNIX etc. 
    address.sin_addr.s_addr = INADDR_ANY;  // Accept connections from any IP address - listens from all interfaces.
    address.sin_port = htons( PORT );    // Server port to open. Htons converts to Big Endian - Left to Right. RTL is Little Endian

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("BINDING SUCCESSFUL\n");

    // Port bind is done. You want to wait for incoming connections and handle them in some way.
    // The process is two step: first you listen(), then you accept()
    printf("LISTENING... \n");
    if (listen(server_fd, 3) < 0) // 3 is the maximum size of queue - connections you haven't accepted
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // returns a brand new socket file descriptor to use for this single accepted connection. Once done, use send and recv
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    char *fileName = (char *) malloc(sizeof(char) * MSG_SIZE);
    while(1){
        struct reqPack *req = (struct reqPack *) malloc(sizeof(struct reqPack));
        valread = read(new_socket , fileName, MSG_SIZE * sizeof(char));  // read infromation received into the buffer
        printf("Client requested for:%s \n", fileName);
        sendFile(new_socket, fileName);
    }
    return 0;
}
