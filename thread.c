#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUMT 256 //쓰레드의 개수
 
void *process(void* param);
long fact(long num);

void *process( void* param ){ 
	long num = 0;
	printf("myid: %ld\n", (long)param); //쓰레드 아이디.
	num = fact((long)10);	//팩토리얼 연산의 수
	pthread_exit( (void*) num );
}

long fact(long num){	//팩토리얼 연산
	long result = 1;
	for(int i = 2; i <= num; i++){
        result *= i;
    }
	return result;
}
static inline long timer()	//쓰레드 기반의 프로그램의 시간 측정
{
	struct timeval tcount;
	gettimeofday (&tcount, NULL);
	return (tcount.tcount_sec * 1000 + tcount.tcount_usec / 1000);
}

int main(){
	pthread_t tid[NUMT]; 
	void *status;
	long i, sum = 0;
	long t, dt;
	t = timer();

	for(i = 1; i <= NUMT; i++){
		printf("Creating %ld\n", i);
		pthread_create(&tid[i - 1], NULL, process, (void *)i); //쓰레드 생성
	}
	
	printf("In main: all threads created\n");

	for(i = 1; i <= NUMT; i++){	//쓰레드의 연산
		printf(" Main: joined %ld\n", i);
		pthread_join(tid[i - 1], &status);	
		printf("Thread %ld returned: %ld\n", i, (long)status);
	}
	
	dt = timer() - t;
	printf("Total of all time = %ld.%ld sec\n", dt / 1000, dt % 1000);	//총 실행시간 출력
    
	return 0;
}