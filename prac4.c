#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
for(int i = 0; i < 5; i++){pid_t pid = fork(); // new process
    if(pid == 0) { // if new process is parent
        printf("\n\nChild => PPID: %d PID: %d\n", getppid(), getpid()); // display process parent id and process id 
        exit(EXIT_SUCCESS); // exit
    } else if(pid > 0) { // if greater then zero so not parent
        printf("\n\nParent => PID: %d\n", getpid()); // display parents id
        printf("\n\nWaiting for child process to finish.\n");
        wait(NULL);
        printf("\n\nChild process finished.\n\n");
    } else {
        printf("\n\nUnable to create child process.\n");
    }}

return EXIT_SUCCESS;
}
