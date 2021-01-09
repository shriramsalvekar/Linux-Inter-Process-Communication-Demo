/*
 * UDP Socket that sends string "Hello".
 * This code demonstrate the Client side mechanism. 
 */ 
#include <stdio.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

// defining Server IP for communication.
#define SERV_IP "192.168.1.1"
// defining Server port for communication. 
#define SERV_PORT 1992
#define MAX 1024 

int main(){ 
    int cfd,n = 0,len = 0; 
    char buffer[MAX]; 
    char str[] = "Hello from client"; 
    struct sockaddr_in serv_addr; 

    // Creating socket file descriptor 
    cfd = socket(AF_INET, SOCK_DGRAM, 0);  
    if(cfd < 0){
	  perror("Client Socket create failed : ");
	  _exit(1);
    }
    printf("client socket created.\n");
    memset(&serv_addr, 0, sizeof(serv_addr)); 

    // Assigning type of Socket. 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);; 
    serv_addr.sin_port = htons(SERV_PORT); 

    // Send string "Hello" to the Server.
    sendto(cfd,(const char*)str, strlen(str),MSG_CONFIRM, (const struct sockaddr *) &serv_addr,sizeof(serv_addr)); 
    printf("Hello message sent.\n"); 

    // Receive string data to the Client.
    n = recvfrom(cfd, buffer, MAX,MSG_WAITALL, (struct sockaddr *) &serv_addr, &len); 
    buffer[n] = '\0'; 
    printf("Server : %s\n", buffer); 

    // closing Client socket descriptor.
    close(cfd); 
    return 0; 
} 
