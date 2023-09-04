#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <netdb.h>


void sendMessage(int fd, const char *data)
{


    int len = strlen(data);
    uint32_t Netlen = htonl(len);
    size_t size_len = sizeof(Netlen);
    send(fd, &Netlen, size_len, 0);
    if(send(fd, data, len, 0) != len){
        printf("Did not send all data");
    }


}

// client
int main(int argc, char **argv)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0); 
    if(fd == -1)
    {
        perror("Socket()");
        return 1;
    }

    if(argc != 2){
        fprintf(stderr, "usgage: ip address");
        exit(1);
    }

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = 0;

    struct addrinfo *addresses = NULL;


    if(getaddrinfo(argv[1],NULL,&hints,&addresses) != 0){
        perror("getaddrinfo");
        exit(1);
    }

    struct addrinfo *address = addresses;
    if(address == NULL){
        perror("ADDRESS IS NULL");
    }


    // while(address){

    //     printf("ai canon name: %s\n", address->ai_canonname);
    //     struct sockaddr_in *sockaddress = (struct sockaddr_in *)address->ai_addr;
    //     char textaddr[32];
    //     inet_ntop(AF_INET, &sockaddress->sin_addr, textaddr, sizeof(textaddr));
    //     printf("addr: %s\n\n", textaddr);


    //     address = address->ai_next;
    // }

    freeaddrinfo(addresses);





    // close(fd);
    // exit(1);




    struct sockaddr_in addr = *((struct sockaddr_in *)(address->ai_addr));
    // memset(&addr, 0, sizeof(addr));
    // if(inet_pton(AF_INET, argv[1], &addr.sin_addr ) != 1){
    //     perror("inet_pton");
       
    // }

   // addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    

    //connect

    if(connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1){
        perror("connect()");
        return 1;
    }


    int num = 123456;
    char *data = "123456";
    sendMessage(fd, data);
    sleep(5);
    sendMessage(fd, data);


    num = htonl(num);
    // if(send(fd, &num, sizeof(num), 0) == -1)
    // {
    //     perror("send()");
    //     return 1;
    // }

   

    if(send(fd, data, strlen(data), 0) == -1)
    {
        perror("send()");
        return 1;
    }

   

    if(shutdown(fd, SHUT_RDWR) == -1)
    {
        perror("shutdown()");
        return 1;
    }

  
    
    close(fd);


    return 0;

}