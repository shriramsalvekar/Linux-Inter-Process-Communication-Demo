/*
 * Simple Chat application in C using UNIX Socket.
 * This code demonstrate the Client side mechanism.
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/un.h>

// defining socket file for communication
#define SOCKET_FILE "comm_sock"

int main(){
    int cfd = 0,ret = 0;
    char buf[512];
    socklen_t len = sizeof(struct sockaddr_un);
    struct sockaddr_un serv_addr;

    // Creating Client Socket descriptor.
    cfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(cfd < 0){
	  perror("Socket Creation failed : ");
	  _exit(1);
    }
    printf("client socket created.\n");

    // Assigning type of Socket.
    printf("client connecting to server socket : %s.\n", SOCKET_FILE);
    memset(&serv_addr, 0, sizeof(struct sockaddr_un));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCKET_FILE);
    ret = connect(cfd, (struct sockaddr*)&serv_addr, len);
    if(ret < 0){
	  perror("Socket Connect failed : ");
	  _exit(1);
    }
    printf("client connected to server socket : %d.\n", ret);

    // Code Logic for chat application. Chat will remain active till "bye" message.
    do{
	  printf("client : ");
	  fgets(buf, sizeof(buf), stdin);
	  write(cfd, buf, strlen(buf) + 1);
	  read(cfd, buf, sizeof(buf));
	  printf("server : %s", buf);
    }while(strcmp(buf, "bye\n") != 0);

    //closing Client socket descriptor.
    close(cfd);
    remove(SOCKET_FILE);
    printf("client socket closed.\n");
    return 0;
}
