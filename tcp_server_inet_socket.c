/*
 * Simple Chat application in C using INET Socket.
 * This code demonstrate the Server side mechanism. 
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// Port Number to use for communication
#define SERV_PORT 1992

int main(){
    int sfd = 0, fd = 0, ret = 0;
    char buf[512];
    socklen_t len = sizeof(struct sockaddr_in);
    struct sockaddr_in serv_addr, cli_addr;

    // Creating Client Socket descriptor.
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0){
	  printf("Server Socket create failed : ");
	  _exit(1);
    }
    printf("server socket created.\n");

    // Assigning type of Socket.
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SERV_PORT);

    // Binding address to the Socket.
    ret = bind(sfd, (struct sockaddr*)&serv_addr, len);
    printf("server socket address assigned : %d.\n", SERV_PORT);

    // listening to server socket with maximum allowed connections are 5.
    listen(sfd, 5);
    printf("server socket listening.\n");

    // Accepting the client connection.
    printf("server waiting for client connection.\n");
    memset(&cli_addr, 0, sizeof(struct sockaddr_in));
    fd = accept(sfd, (struct sockaddr*)&cli_addr, &len);
    if(fd < 0){
	  perror("Server accept failed : ");
	  _exit(1);
    }
    printf("server accepted for client connection.\n");

    // Code Logic for chat application. Chat will remain active till "bye" message.
    do{
	  read(fd, buf, sizeof(buf));
	  printf("client : %s", buf);
	  printf("server : ");
	  fgets(buf, sizeof(buf), stdin);
	  write(fd, buf, strlen(buf) + 1);
    }while(strcmp(buf, "bye\n") != 0);

    // closing Server socket descriptor.
    close(fd);
    shutdown(sfd, SHUT_RDWR);
    printf("closed server listening socket.\n");
    return 0;
}


