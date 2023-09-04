
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; // shared data between threads
void *runner(void *param); // threads call this function

int main(int argc, char *argv[]) {
 pthread_t tid; //thread identifier
 pthread_attr_t attr;  //set of thread attributes
 if (argc != 2) {
 fprintf(stderr, "Usage a.out <integer value>\n");
 return EXIT_FAILURE;
 }

 if (atoi(argv[1])<0) {
 fprintf(stderr, "%d must be >= 0\n", atoi(argv[1]));
 return EXIT_FAILURE;
 }

 /* get thread attributes */
 pthread_attr_init(&attr);

 /* create thread */
 pthread_create(&tid, &attr, runner, argv[1]);

 /* wait for thread to exit */
 pthread_join(tid, NULL); 
 printf("\nApplication to demonstrate basic Multithreaded Application\n\n----------------------------------\n");
 printf("The sum of the numbers from 1 to %d is = %d\n", atoi(argv[1]), sum);
 printf("----------------------------------\n");
}

/* The thread will begin control in this function */
void *runner(void *param) {
 int upper = atoi(param);
 sum=0;
 for (int i=0; i <= upper; i++) {
    sum +=i;
 }
 pthread_exit(0);
}
