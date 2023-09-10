#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1023
int main(int argc, char **argv) {
/* client file descriptor */


/* receive buffer */
char buffer[BUFFER_SIZE];
struct sockaddr clientaddr;
socklen_t clientaddr_len = sizeof(clientaddr);



/* Check user has passed in the port number at the command line
* local host will be used as the default address
*/
if(argc != 2){
        fprintf(stderr, "usgage: port number");
        exit(1);
    }



/* Create a TCP/IP socket making sure to select appropriate family,
communication type &
* protocol
*/

int listensockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if(listensockfd == -1)
    {
        perror("Socket()");
        return 1;
    }

    

/* Declare a data structure to specify the socket address (IP Address + Port)
* Complete the Internet socket address structure
* An IPv4 socket address structure - use memset to zero the struct out
*/


struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));


/* Assign a name to the socket created - Implement bind() system call */
/* Place server in passive mode - listen for incomming client request */
/* infinite loop */
if(bind(listensockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("bind()");
        return 1;
    }

 if(listen(listensockfd, 10) == -1){
        perror("listen()");
        return 1;
    }

while (1) {
    int clientfd = accept(listensockfd,(struct sockaddr *)&clientaddr,&clientaddr_len);
    if(clientfd == -1){
        perror("accept");
        return 1;
    }

    int bytes_received = recv(clientfd, buffer, sizeof(buffer)-1, 0); 
    if(bytes_received == -1){
        perror("recv");
        return 1;
    }
    buffer[bytes_received] = '\0';
    printf("Received from client: %s\n", buffer);
    




/* close the socket used to receive data */
if(close(clientfd) == -1)
    {
        perror("close(clientfd)");
        return 1;
    }

    
  
    


} // end while


/* shutdown the connection - end communication to and from the socket
SHUT_RDWR */


 if(shutdown(listensockfd, SHUT_RDWR) == -1)
    {
        perror("shutdown()");
        return 1;
    }

/* sockets can remain open after program termination - close listening
socket*/

if(close(listensockfd) == -1)
    {
        perror("close(listensockfd)");
        return 1;
    }

}