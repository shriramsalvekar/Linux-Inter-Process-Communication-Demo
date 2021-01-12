/*
 * C Program that creates new process called Child Process. 
 * This Example demonstrates table which gets written by Parent & Child Process individually.
 */

#include <stdio.h>
#include <unistd.h>

int main(){
   int i = 0,num = 5;
    
   // system call to create new Child process
   int ret = fork();
	  
   // fork returns exactly zero for Child Process
   if(ret == 0){
	  // PID of Child Process
	  printf("Child PID : %d\n",getpid());
	  for(i = 1 ; i <= 10 ; i++){
		printf("%d x %d = %d\n",num, i, num * i);
		sleep(1);
	  }
   }
   else{
	  // PID of Parent Process
	  printf("Parent PID : %d\n",getpid());
	  for(i = 1 ; i <= 10 ; i++){
		printf("%d x %d = %d\n",num,i,num*i);
		sleep(1);
	  }
   }
    
   //End of Program
   printf("End of Program !!\n");
   return 0;
}
