/*
 *  Sample Code to demonstrate the addition using thread creation(POSIX Thread).
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Basic Array is declared.
#define MAX 5
int arr[MAX] = {1,2,3,4,5};

// Required thread function signature.
void* addition(void *param){
    int i, res = 0;
    int *arr = (int*)param;

    printf("Performing Addition in thread function.\n");
    // Simple logic to add all number to a singl value.
    for(i=0; i<MAX; i++)
	  res = res + arr[i];
    pthread_exit((void*)res);
    //return (void*)res;
}

int main(){
    int ret = 0, result = 0;
    pthread_t ta;

    // Creating Thread.
    printf("Creating Thread for Addition...\n");
    ret = pthread_create(&ta, NULL, addition, arr);

    // thread calling pthread_join() will wait for given thread.
    pthread_join(ta, (void**)&result);
    printf("Final Result : %d\n", result);
    return 0;
}
