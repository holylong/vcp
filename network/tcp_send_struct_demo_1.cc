#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  

#ifdef __unix__
#include <sys/socket.h>  
#include <arpa/inet.h>  
#include <unistd.h>  
#define closesocket close;
#elif defined(_WIN32)
#include <Windows.h>
#endif

#define SERVER_IP "127.0.0.1"

// 定义结构体  
struct Data {  
    int id;  
    char name[20];  
};  
  
int main(int argc, char* argv[]) {

    const char* ip = SERVER_IP;
    if(argc == 2){
        ip = argv[1];
    }

    fprintf(stdout, "ip:%s\n", ip);

    int sockfd;  
    struct sockaddr_in server_addr;  
    struct Data data = { 1, "John" };  
  
    // 创建套接字  
    sockfd = socket(AF_INET, SOCK_STREAM, 0);  
    if (sockfd < 0) {  
        perror("socket error");  
        exit(EXIT_FAILURE);  
    }  
  
    // 设置服务器地址信息  
    memset(&server_addr, 0, sizeof(server_addr));  
    server_addr.sin_family = AF_INET;  
    server_addr.sin_addr.s_addr = inet_addr(ip); // 修改为服务器地址  
    server_addr.sin_port = htons(8888); // 修改为服务器端口号  
  
    // 连接服务器  
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {  
        perror("connect error");  
        exit(EXIT_FAILURE);  
    }  
  
    // 发送结构体数据  
    if (send(sockfd, (const char*)&data, sizeof(data), 0) < 0) {  
        perror("send error");  
        exit(EXIT_FAILURE);  
    }  
  
    printf("Data sent successfully\n");  
  
    // 关闭套接字  
    closesocket(sockfd);  
  
    return 0;  
}