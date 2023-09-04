#include "buffer.h"

#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

#include <semaphore.h>

#include <unistd.h>

#define TRUE 1
buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int insertPointer = 0, removePointer = 0;
void * producer(void * param);
void * consumer(void * param);

int insert_item(buffer_item item) {
  sem_wait(&empty);
  pthread_mutex_lock(&mutex);
  buffer[insertPointer++] = item;
  insertPointer = insertPointer % BUFFER_SIZE;
  pthread_mutex_unlock(&mutex);
  sem_post(&full);
  return 0;
}

int remove_item(buffer_item * item) {
  sem_wait(&full);
  pthread_mutex_lock(&mutex);
  *item = buffer[removePointer++];
  removePointer = removePointer % BUFFER_SIZE;
  pthread_mutex_unlock(&mutex);
  sem_post(&empty);
  return 0;
}

int main(int argc, char * argv[]) {
    int sleepTime, producerThreads, consumerThreads;
    int i;

    if (argc != 4) {
      fprintf(stderr, "Usage: <sleep time> <producer threads> <consumer threads>\n");
      return -1;
    }

    sleepTime = atoi(argv[1]);
    producerThreads = atoi(argv[2]);
    consumerThreads = atoi(argv[3]);

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_t producers[producerThreads], consumers[consumerThreads];

    for(i = 0; i < producerThreads; i++) {
      pthread_create(&producers[i], NULL, producer, NULL);
    }

    for(i = 0; i < consumerThreads; i++) {
      pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    sleep(sleepTime);

    return 0;
}

void * producer(void * param) {
  buffer_item random;
  int r;
  while (TRUE) {
    r = rand() % 5;
    sleep(r);
    random = rand();
    if (insert_item(random)) {
      fprintf(stderr, "Error");
    } else {
      printf("Producer produced %d \n", random);
    }
  }
}

void * consumer(void * param) {
  buffer_item random;
  int r;
  while (TRUE) {
    r = rand() % 5;
    sleep(r);
    if (remove_item(&random)) {
      fprintf(stderr, "Error Consuming");
    } else {
      printf("Consumer consumed %d \n", random);
    }
  }
}
