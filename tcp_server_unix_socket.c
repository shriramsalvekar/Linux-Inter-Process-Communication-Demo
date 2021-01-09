/*
 *  Simple Chat application in C using UNIX Socket.
 *  This code demonstrate the Server side mechanism.
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/un.h>

// defining socket file for communication
#define SOCKET_FILE "comm_sock"

int main(){
    int sfd = 0, fd = 0,ret = 0;
    char buf[512];
    socklen_t len = sizeof(struct sockaddr_un);
    struct sockaddr_un serv_addr, cli_addr;

    // Creating Server (listening) Socket descriptor.
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sfd < 0){
	  perror("Server socket create failed : ");
	  _exit(1);
    }
    printf("server socket created.\n");

    // Assigning type of Socket.
    memset(&serv_addr, 0, sizeof(struct sockaddr_un));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCKET_FILE);

    // Binding address to the Socket.
    ret = bind(sfd, (struct sockaddr*)&serv_addr, len);
    printf("server socket address assigned : %s.\n", SOCKET_FILE);

    // listening to server socket with maximum allowed connections are 5.
    listen(sfd, 5);
    printf("server socket listening.\n");

    // Accepting the client connection.
    printf("server waiting for client connection.\n");
    fd = accept(sfd, (struct sockaddr*)&cli_addr, &len);
    if(fd < 0){
	  perror("Server Socket accept failed : ");
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
    printf("server listening socket closed.\n");
    return 0;
}
