/*
 * Simple Chat application in C using INET Socket. 
 * This code demonstrate the Client side mechanism.
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/un.h>
#include <arpa/inet.h>

// Server IP to connect 
#define SERV_IP "192.168.1.1"
// Port Number to use for communication
#define SERV_PORT 1992

int main(){

    int cfd = 0,ret = 0;
    char buf[512];
    socklen_t len = sizeof(struct sockaddr_in);
    struct sockaddr_in serv_addr;
    // Creating Client Socket descriptor. 
    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if(cfd < 0){
	  perror("Client Socket create failed : ");
	  _exit(1);
    }
    printf("client socket created.\n");

    // Assigning type of Socket.
    printf("client connecting to server socket : %s:%d.\n", SERV_IP, SERV_PORT);
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);
    serv_addr.sin_port = htons(SERV_PORT);
    ret = connect(cfd, (struct sockaddr*)&serv_addr, len);
    if(ret < 0){
	  perror("Unable to connect : ");
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

    // closing Client socket descriptor. 
    close(cfd);
    printf("closed client socket.\n");
    return 0;
}
