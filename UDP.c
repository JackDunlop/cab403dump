#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE 1023
 
int main(int argc, char **argv){
	
	/* check port number is passed in in on command line */		
    if(argc != 2){
        fprintf(stderr, "usgage: ip address");
        exit(1);
    }	
	
	/* variables required for solution */
	int sockfd;	
	struct sockaddr_in server_addr, client_addr;
	char buffer[BUFFER_SIZE];
	socklen_t addr_size;
	char *ip = "127.0.0.1";
	bool cont = true;
	
	
	/* Create a UDP Socket */ 
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sockfd == -1)
    {
        perror("Socket()");
        return 1;
    }

	
	/* Initialise the sockaddr_in structure 
	 * use memset to zero the struct out
	*/	
	
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
	
	/* bind server address to socket descriptor */
	if(bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr)) == -1){
        perror("Bind(UDP_SOCK)");
        return 1;
    }

	while (cont) {

		/* clear buffer */
        memset(&buffer,0,sizeof(buffer));
			
		/* Calculating the Client Datagram length */

        
		/* use recvfrom to receive data from client */
        int numbytes = recvfrom(sockfd,&buffer,BUFFER_SIZE,0,(struct sockaddr *)&client_addr,&addr_size);
        if(numbytes == -1){
            perror("recvfrom");
            return 1;
        }

			
		/* Output the message from the client */		
        buffer[numbytes] = '\0';
        printf("Received from client: %s\n", buffer);
    

		/* If termination message sent from server exit while loop*/
		if(strcmp(buffer, "TERMINATE") == 0) {
        cont = false;
        continue; // skip to the next iteration to bypass sending a response
        }	
	
		/* Clear the buffer and send a message from the server to the client */
        memset(&buffer,0,sizeof(buffer)); // cleared
        if((numbytes = sendto(sockfd, &buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, addr_size)) == -1)
        {
            perror("sendto()");
            return 1;
        }
			
	}

	// Closing the Socket File Descriptor.
	close(sockfd);
	return 0;
}
