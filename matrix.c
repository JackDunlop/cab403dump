#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



#define N 1500
#define NUM_THREADS 4
double** A, ** B, ** C;
void *FOO(void *threadid)
{
    long tid;
    tid = (long)threadid;
    int itemsPerThread = (N + NUM_THREADS - 1) / NUM_THREADS;
    int startIndex = itemsPerThread * tid;
    int endIndex = fmin(startIndex + itemsPerThread, N);

    for (int i = startIndex; i < endIndex; i++) {
        for (int k = 0; k < N; k++) {
            for (int l = 0; l < N; l++) {
                C[i][l] += A[i][k] * B[k][l];  
            }
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    A = (double**) malloc(N * sizeof(double*));
    B = (double**) malloc(N * sizeof(double*));
    C = (double**) malloc(N * sizeof(double*));

    for (int i = 0; i < N; i++) {
        A[i] = (double*) malloc(N * sizeof(double));  
        B[i] = (double*) malloc(N * sizeof(double));
        C[i] = (double*) malloc(N * sizeof(double));
        for (int j = 0; j < N; j++) {
            A[i][j] = rand();
            B[i][j] = rand();
            C[i][j] = 0;  
        }
    }


    pthread_t thread[NUM_THREADS];
    long id[NUM_THREADS];
    struct timespec start, end;
    clock_gettime(CLOCKS_PER_SEC, &start);
    for(int i = 0; i < NUM_THREADS; i++)
    {   
        id[i] = i;
        pthread_create(&thread[i], NULL, FOO, (void *)id[i]);
    }
   

    for(int i =0; i < NUM_THREADS; i++)
        pthread_join(thread[i], NULL);


    clock_gettime(CLOCKS_PER_SEC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec);
    printf("Time taken: %f seconds\n", elapsed_time); 
     // Free the allocated memory
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
    pthread_exit(NULL);
    return 0;
}
 