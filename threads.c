#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 42
#define NUM_THREADS 4
void *FOO(void *threadid)
{
    long tid;
    tid = (long)threadid;
   // printf("Hello World! FROM THREAD %ld! \n",tid);
	int itemsPerThread = (N + NUM_THREADS - 1) / NUM_THREADS;
	int startIndex = itemsPerThread * tid;
	int endIndex = fmin(startIndex + itemsPerThread, N);
	for(int j = startIndex; j < endIndex; j++)
    printf("Some computations %d done on %ld\n", j, tid);
    return 0;
}

int main(int argc, char **argv)
{
    printf("Hello World! \n");

    pthread_t thread[NUM_THREADS];
    long id[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++)
    {   
        id[i] = i;
        pthread_create(&thread[i], NULL, FOO, (void *)id[i]);
    }
       

    for(int i =0; i < NUM_THREADS; i++)
        pthread_join(thread[i], NULL);
    
    
    pthread_exit(NULL);
    return 0;
}
 