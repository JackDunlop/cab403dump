#include <pthread.h>
#include <stdio.h>

int globalVar = 0;
pthread_mutex_t lock;
void *addMillion(void *arg);

int main(int argc, char *argv[]) {
    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1, NULL, addMillion, NULL);
    pthread_create(&thread2, NULL, addMillion, NULL);
    pthread_create(&thread3, NULL, addMillion, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    printf("\n\nTotal for globalVar = %d\n", globalVar);
    return 0;
}

void *addMillion(void *arg) {  
    pthread_mutex_lock(&lock); 
    for (int i = 0; i < 1000000; i++) {
        globalVar++;
    }    
    pthread_mutex_unlock(&lock); 
    return NULL;
}
