//Thread use example program that splits odd and even threads (8 total)
//to perform different tasks and join again in main. 
//All results are passed from the thread to main and printed there.
//To compile: gcc ThreadedFactorialSums.c -lpthread
#include <pthread.h>
#include <studio.h>
#include <stdlib.h>
#define NUMT 8 //Num threads

//longs are used instead of ints due to the type casting to void pointers
//to pass and return them to the threads. 
void *process(void* param);
long fact(long num);
//-----------------------------------------------------------
//-----------------------------------------------------------
void *process( void* param ){ //Function where the threads begin and split based on odd/even thread IDs (1-8).

	long num = 0;
	printf("myid: %ld\n", (long)param); //쓰레드 아이디.
	num = fact((long)param);
	pthread_exit( (void*) num );
}

long fact(long num){
	long result = 1;
	for(int i = 2; i <= num; i++){
        result *= i;
    }
	return result;
}
//-----------------------------------------------------------
//-----------------------------------------------------------
int main(){
	pthread_t tid[NUMT]; //store pthread IDs in array
	void *status;
	long i, sum = 0;

	for(i = 1; i <= NUMT; i++){
	printf("Creating %ld\n", i);
	pthread_create(&tid[i - 1], NULL, process, (void *)i); //쓰레드 생성
	}

        printf("In main: all threads created\n");

	for(i = 1; i <= NUMT; i++){
		printf(" Main: joined %ld\n", i);
		pthread_join(tid[i - 1], &status);
		printf("Thread %ld returned: %ld\n", i, (long)status);
	}
 
    return 0;
}
