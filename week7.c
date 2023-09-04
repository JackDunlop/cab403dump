#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
// server

char *recvMessage(int fd)
{

    char *data;
    uint32_t len;
     size_t size_len = sizeof(len);
     int recvint = recv(fd, &len, size_len, 0);
    if(recvint!= size_len){
        fprintf(stderr, "did not recv valid len value, got amount %d", recvint);
        exit(1);
    }
    len = ntohl(len);
    data = malloc(len + 1);
    if(recv(fd, data, len, 0) != len){
        fprintf(stderr, "did not recv valid len data");
        exit(1);
    }

    data[len] = "\0";

    return data;


}

int main()
{
    int listensockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if(listensockfd == -1)
    {
        perror("Socket()");
        return 1;
    }

    int opt_e = 1;
    if(setsockopt(listensockfd, SOL_SOCKET, SO_REUSEADDR, &opt_e, sizeof(opt_e)) == -1){
        perror("setsockopt");
        return 1;
    }
    

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    

    if(bind(listensockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("bind()");
        return 1;
    }

    if(listen(listensockfd, 10) == -1){
        perror("listen()");
        return 1;
    }

    struct sockaddr clientaddr;
    socklen_t clientaddr_len = sizeof(clientaddr);

    int clientfd = accept(listensockfd,(struct sockaddr *)&clientaddr,&clientaddr_len);
    if(clientfd == -1){
        perror("accept");
        return 1;
    }

    

    // char buffer[1024];
    // int num;
    // int bytes_received = recv(clientfd, &num, sizeof(num), 0);

    // if(bytes_received == -1){
    //     perror("recv");
    //     return 1;

    // }

    // buffer[bytes_received] = "\0";
    // num = ntohl(num);
    // printf("Received from client: %d\n", num);
    

    // char buffer[1024];
    // int bytes_received = recv(clientfd, buffer, 1023, 0);

    // if(bytes_received == -1){
    //     perror("recv");
    //     return 1;

    // }

    // buffer[bytes_received] = "\0";
    // printf("Received from client: %s", buffer);

    char *data1 = recvMessage(clientfd);
    printf("msg1 :%s\n", data1);
    char *data2 = recvMessage(clientfd);
    printf("msg2 :%s\n", data2);

    free(data1);
    free(data2);

    if(shutdown(clientfd, SHUT_RDWR) == -1)
    {
        perror("shutdown()");
        return 1;
    }

    if(close(clientfd) == -1)
    {
        perror("close(clientfd)");
        return 1;
    }

    
    if(close(listensockfd) == -1)
    {
        perror("close(listensockfd)");
        return 1;
    }
    


    return 0;

}