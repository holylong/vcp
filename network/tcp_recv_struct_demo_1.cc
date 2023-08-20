#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  

#ifdef __unix__ 
#include <sys/socket.h>  
#include <arpa/inet.h>  
#include <unistd.h>

#define closesocket close;
#elif defined(_WIN32)
#include <WS2tcpip.h>
#endif

// struct define
struct Data {  
    int id;  
    char name[20];  
};  
  
int main() {  
    int sockfd;  
    struct sockaddr_in server_addr, client_addr;  
    struct Data data;  
    socklen_t client_len = sizeof(client_addr);  
  
    // socket create
    sockfd = socket(AF_INET, SOCK_STREAM, 0);  
    if (sockfd < 0) {  
        perror("socket error");  
        exit(EXIT_FAILURE);  
    }  
  
    // set server addresss message  
    memset(&server_addr, 0, sizeof(server_addr));  
    server_addr.sin_family = AF_INET;  
    server_addr.sin_addr.s_addr = INADDR_ANY;  
    server_addr.sin_port = htons(8888);  
  
    // bind socket to server address  
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {  
        perror("bind error");  
        exit(EXIT_FAILURE);  
    }  
  
    // listen connection  
    if (listen(sockfd, 5) < 0) {  
        perror("listen error");  
        exit(EXIT_FAILURE);  
    }  
  
    printf("Waiting for a connection...\n");  
  
    // accept connection  
    int connfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);  
    if (connfd < 0) {  
        perror("accept error");  
        exit(EXIT_FAILURE);  
    }  
  
    printf("Connection accepted from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));  
  
    // recv struct data  
#ifdef _WIN32
    if (recv(connfd, (char*)&data, sizeof(data), 0) < 0) {  
#else
    if (recv(connfd, &data, sizeof(data), 0) < 0) {  
#endif
        perror("recv error");  
        exit(EXIT_FAILURE);  
    }  
  
    printf("Received data: id = %d, name = %s\n", data.id, data.name);  
  
    // close socket and connection  
    closesocket(connfd);  
    closesocket(sockfd);  
  
    return 0;  
}