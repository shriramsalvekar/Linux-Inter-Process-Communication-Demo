/*
 * UDP Socket that sends string "Hello".
 * This code demonstrate the Server side mechanism. 
 */ 
#include <stdio.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

// defining Server port for communication. 
#define SERV_PORT	 1992 
#define MAX 1024 

int main(){ 
    int sfd,ret = 0,n = 0; 
    char buffer[MAX]; 
    char str[] = "Hello from server"; 
    struct sockaddr_in serv_addr, cli_addr; 
    int len = sizeof(cli_addr); 

    // Creating socket file descriptor 
    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sfd < 0){ 
	  perror("socket creation failed"); 
	  _exit(1); 
    } 
    printf("server socket created\n");

    memset(&serv_addr, 0, sizeof(serv_addr)); 
    memset(&cli_addr, 0, sizeof(cli_addr)); 

    // Assigning type of Socket. 
    serv_addr.sin_family = AF_INET; // IPv4 
    serv_addr.sin_addr.s_addr = INADDR_ANY; 
    serv_addr.sin_port = htons(SERV_PORT); 

    // Bind the socket with the server address 
    ret = bind(sfd, (const struct sockaddr *)&serv_addr,sizeof(serv_addr)); 

    // Receive string data from the Client.
    n = recvfrom(sfd, (char *)buffer, MAX,MSG_WAITALL,( struct sockaddr *) &cli_addr,&len); 
    buffer[n] = '\0'; 
    printf("Client : %s\n", buffer); 

    // Sending back the string "Hello" to the Client.
    sendto(sfd, (const char *)str, strlen(str),MSG_CONFIRM,(const struct sockaddr*)&cli_addr,len); 
    printf("Hello message sent.\n"); 

    // closing Server socket descriptor.
    close(sfd);
    return 0; 
} 
