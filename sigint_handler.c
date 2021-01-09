/*  
 *  Simple C program that demonstrates the catching of SIGINT signal(Ctrl+c).
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// Signal Handler for SIGINT signal
void sigint_handler(int signal_number){
    // Print the Signal number of SIGINT(2).
    printf("signal SIGINT caught : %d\n", signal_number);
    _exit(0);
}

int main(){
    int i=0, ret;
    struct sigaction sa1, sa2;

    // Assigning the signal handler for SIGINT
    sa1.sa_handler = sigint_handler;
    ret = sigaction(SIGINT, &sa1, &sa2);
    if(ret < 0){
	  perror("sigaction() failed");
	  _exit(1);
    } 

    // Infinite While Loop
    while(1){
	  printf("running : %d\n", ++i);
	  sleep(1);
    } 

    return 0;
}
