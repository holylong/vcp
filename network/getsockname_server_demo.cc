#define MAXLINE 4096
#define PORT 6563
#define LISTENQ 1024
#define BUFFER_SIZE 4096
 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#ifdef _WIN32
#include <ws2tcpip.h>
#include <windows.h>
#ifndef INET_ADDRSTRLEN
#define INET_ADDRSTRLEN 16
#endif

typedef int socklen_t;

#else
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define closesocket close
#endif

#include <basesocket.h>

int main() {
#ifdef _WIN32
    wanda::net::WinSockInitial initialer;
#endif
    int n;
    char buff[BUFFER_SIZE];
    int listenfd, connfd;
    
    struct sockaddr_in servaddr;
    struct sockaddr_in listendAddr, connectedAddr, peerAddr;

    int listendAddrLen, connectedAddrLen, peerLen;
    char ipAddr[INET_ADDRSTRLEN];
 
    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
 
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
 
    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1 ){//服务器端绑定地址
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
 
    if( listen(listenfd, LISTENQ) == -1){
        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
 
    listendAddrLen = sizeof(listendAddr);
    
    if(getsockname(listenfd, (struct sockaddr *)&listendAddr, (socklen_t*)&listendAddrLen) == -1){
        printf("getsockname error\n");
        exit(0);
    }
    printf("listen address = %s:%d\n", inet_ntoa(listendAddr.sin_addr), ntohs(listendAddr.sin_port));
 
    printf("======waiting for client's request======\n");
    while(1) {
        if( (connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) == -1 ){
            printf("accept socket error: %s(errno: %d)", strerror(errno), errno);
            continue;
        }
 
        connectedAddrLen = sizeof(connectedAddr);
        if(getsockname(connfd, (struct sockaddr *)&connectedAddr, (socklen_t*)&connectedAddrLen) == -1){
            printf("getsockname error\n");
            exit(0);
        }

        printf("connected server address = %s:%d\n", inet_ntoa(connectedAddr.sin_addr), ntohs(connectedAddr.sin_port));
 
        //获取connfd表示的连接上的对端地址
        peerLen = sizeof(peerAddr);
        if(getpeername(connfd, (struct sockaddr *)&peerAddr, (socklen_t*)&peerLen) == -1){
            printf("getpeername error\n");
            exit(0);
        }

        printf("connected peer address = %s:%d\n", inet_ntop(AF_INET, &peerAddr.sin_addr, ipAddr, sizeof(ipAddr)), ntohs(peerAddr.sin_port));
 
        n = recv(connfd, buff, MAXLINE, 0);
        buff[n] = '\0';
        printf("recv msg from client: %s\n", buff);
        closesocket(connfd);
    }
 
    closesocket(listenfd);
    return 0;
}