/* 
 * Simple C program that demonstrates the Communication between two Processes.
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define READ_END  0
#define WRITE_END 1

int main(){
    int arr[2] = {0};
    char buf[32] = "Hello";

    // pipe is used to send data from one process to another process.
    int pipe_ret = pipe(arr);

    // System Call fork() is used to create new Child Process.
    int ret = fork();
    if(ret == 0){
	  // Closed read end of pipe.
	  close(READ_END);

	  // sending string data to another process.
	  printf("child : sending data ... %s\n", buf);
	  write(arr[WRITE_END], buf, strlen(buf)+1);

	  close(arr[WRITE_END]);
    }
    else{
	  // Closed write end of pipe.
	  close(arr[WRITE_END]);

	  // receiving string data from process.
	  printf("parent : receiving data ...\n");
	  read(arr[READ_END], buf, sizeof(buf));
	  printf("parent : data received : %s\n", buf);

	  close(arr[READ_END]);

    }
    return 0;
}

