#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>


#define NUM_THREADS 4
long long N;
double* A;
double totalSequential;
clock_t start;
pthread_mutex_t lock;

void StartTiming()
{
    start = clock();
}

double StopTiming()
{
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    return time_spent;
}

void *Sum(void *threadid)
{
    long tid;
    tid = (long)threadid;
    double itemsPerThread = (N + NUM_THREADS - 1) / NUM_THREADS;
    double startIndex = itemsPerThread * tid;
    double endIndex = fmin(startIndex + itemsPerThread, N);

	for (long long i = startIndex; i < endIndex;i++) {
		pthread_mutex_lock(&lock);
		totalSequential += A[i];
		pthread_mutex_unlock(&lock);
	}
	
    return 0;
}

int main(int argc, char* argv[]) {
    for (N = 10; 1 ; N *= 10)
	{
		printf("N = %lld\n", N);

    A = (double *) malloc(N * sizeof(double));
    for (long long i = 0; i < N; i++){
        A[i] = 1.0;
    }
        

    StartTiming();
    totalSequential = 0;
    pthread_t thread[NUM_THREADS];
    long id[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; i++)
    {   
        id[i] = i;
        pthread_create(&thread[i], NULL, Sum, (void *)id[i]);
    }
    
    for(int i = 0; i < NUM_THREADS; i++)
    {   
        id[i] = i;
        pthread_join(thread[i], NULL);
    }


    double sequentialTime = StopTiming();
    printf("Sequential total %f, %f seconds\n", totalSequential, sequentialTime);

    free(A);
    free(thread);
    free(id);
    }

    return 0;
}






/*#include <chrono>
using namespace std::chrono;

long long N = 10;
double* A;
double totalSequential;
high_resolution_clock::time_point startTime;

void StartTiming() {
	startTime = high_resolution_clock::now();
}

double StopTiming() {
	duration<double> duration = high_resolution_clock::now() - startTime;
	return duration.count();
}

int main(int argc, char* argv[]) {
	N = 10;

	A = new double[N];
	for (long long i = 0; i < N; i++)
		A[i] = 1.0;

	StartTiming();
	totalSequential = 0;
	for (long long i = 0; i < N; i++)
		totalSequential += A[i];
	double sequentialTime = StopTiming();
	printf("Sequential total %f, %f seconds\n", totalSequential, sequentialTime);

	return 0;
}*/