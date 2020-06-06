//Thread use example program that splits odd and even threads (8 total)
//to perform different tasks and join again in main. 
//All results are passed from the thread to main and printed there.
//To compile: gcc ThreadedFactorialSums.c -lpthread
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUMT 8 //Num threads

//longs are used instead of ints due to the type casting to void pointers
//to pass and return them to the threads. 
void *process(void* param);
long fact(long num);
long sum(long num);
//-----------------------------------------------------------
//-----------------------------------------------------------
void *process( void* param ){ //Function where the threads begin and split based on odd/even thread IDs (1-8).

	long num = 0;
	//printf("myid: %ld\n", (long)param); //Display the thread IDs.

	if((long)param % 2 == 1){//Odd threads. Find factorial.
		num = fact((long)param);
	}
	else{//Even threads. Find summation.
		num = sum((long)param);
	}

	pthread_exit( (void*) num ); //Stop the thread after work is complete and send return value.
}

long fact(long num){ //Return factorial from 1 to num (iterative function, not recursive).
	long result = 1;
	for(int i = 2; i <= num; i++){
        result *= i;
    }
	return result;
}
long sum(long num){ //Return summation from 1 to num.
	long result = 0;
	for(int i = 0; i <= num; i++){
        result += i;
    }
	return result;
}
//-----------------------------------------------------------
//-----------------------------------------------------------
int main(){
	pthread_t tid[NUMT]; //store pthread IDs in array
	void *status;
	long i, sum = 0;
	//printf("In main: time to build threads\n");

	for(i = 1; i <= NUMT; i++){
		//printf("Creating %ld\n", i);
		pthread_create(&tid[i - 1], NULL, process, (void *)i); //type cast i to a void pointer and start the threads in the process function.
	}

	//printf("In main: all threads created\n");

	for(i = 1; i <= NUMT; i++){
		//printf(" Main: joined %ld\n", i);
		pthread_join(tid[i - 1], &status); //Waits on thread ID tid[i] (0 to 8 in order) to finish before moving on. Store the return value in status.
		printf("Thread %ld returned: %ld\n", i, (long)status);
        sum += (long)status;
	}
    printf("Total of all results: %ld\n", sum);
    return 0;
}
