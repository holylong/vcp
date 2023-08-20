#define PORT 6563
#define SEND_SIZE 4096
 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#ifdef _WIN32
#include <ws2tcpip.h>
#include <windows.h>
typedef int socklen_t;
#define INET_ADDRSTRLEN 16
#else
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

#define closesocket close
#endif 

#include <basesocket.h>


int main(int argc, char **argv) {
#ifdef _WIN32
    wanda::net::WinSockInitial initialer;
#endif

    struct sockaddr_in servaddr;//服务器端地址
    struct sockaddr_in clientAddr;//客户端地址
 
    int sockfd;
    int clientAddrLen = sizeof(clientAddr);
    char ipAddress[INET_ADDRSTRLEN];//保存点分十进制的ip地址
    char sendline[SEND_SIZE];
 
    if(argc < 2) {
        printf("parameter error");
    exit(0);
    }
 
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
 
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
 
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
        printf("server address error. addr: %s\n", argv[1]);//地址参数不合法
    exit(0);
    }
 
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) {
        printf("connnect error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
 
    if(getsockname(sockfd, (struct sockaddr*)&clientAddr, (socklen_t*)&clientAddrLen) == -1 ){
        printf("getsockname error: %s(errno: %d))\n", strerror(errno), errno);
        exit(0);
    }
    printf("client:client ddress = %s:%d\n", inet_ntop(AF_INET, &clientAddr.sin_addr, ipAddress, sizeof(ipAddress)), ntohs(clientAddr.sin_port));
 
    while(true){
        printf("send msg to server: \n");
        fgets(sendline, 4096, stdin);
        if(send(sockfd, sendline, strlen(sendline), 0) < 0){
            printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
            exit(0);
        }
    }
 
    closesocket(sockfd);
    return 0;
}