#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_unix_) || defined(__linux__)
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

typedef int SOCKET;
#define closesocket close
#elif defined(_WIN32)
#include <WinSock2.h>
#include <ws2tcpip.h>
#endif

#define SERVER_IP "0.0.0.0" // 服务器IP地址
#define SERVER_PORT 8888 // 服务器端口号

int main(int argc, char* argv[])
{
    SOCKET sock, client_sock; // 套接字描述符
    struct sockaddr_in server, client; // 服务器和客户端地址结构体

    // data will recving
    int data;
    int n; // 发送或接收的字节数
    int len; // 客户端地址长度

    // create a tcp socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("socket failed");
        exit(1);
    }

    // 设置服务器地址结构体
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    // 绑定套接字到指定的地址和端口
    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("bind failed");
        exit(2);
    }

    // 监听客户端的连接请求，设置最大连接数为5
    if (listen(sock, 5) == -1)
    {
        perror("listen failed");
        exit(3);
    }

    printf("Waiting for client connection...\n");

    // 接受一个客户端的连接，返回一个新的套接字描述符
    len = sizeof(client);
    client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&len);
    if (client_sock == -1)
    {
        perror("accept failed");
        exit(4);
    }

    printf("Connected to client: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
#if 0
    // 接收客户端发送的整型数据
    n = recv(client_sock, &data, sizeof(data), 0);
    if (n == -1)
    {
        perror("recv failed");
        exit(5);
    }
    printf("Received %d bytes from client\n", n);

    // convert byte endian to host endian
    data = ntohl(data);
#else
    // recv int from client
    unsigned char recvbuf[4];

#ifdef _WIN32
    n = recv(client_sock, (char*)recvbuf, sizeof(recvbuf), 0);
#else
    n = recv(client_sock, recvbuf, sizeof(recvbuf), 0);
#endif

    if (n == -1)
    {
        perror("recv failed");
        exit(5);
    }
    printf("Received %d bytes from client\n", n);
    data = (recvbuf[0] & 0xff) | (recvbuf[1] << 8) & 0xff00 | (recvbuf[2]<< 16)&0xff0000 | (recvbuf[3] << 24)&0xff000000;
#endif
    // display recv data
    printf("Data: %d\n", data);

    // close socket
    closesocket(client_sock);
    closesocket(sock);

    return 0;
}
