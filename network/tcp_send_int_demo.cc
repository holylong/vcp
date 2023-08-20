/*
 * @Author: holylong mrhlingchen@163.com
 * @Date: 2023-08-14 14:15:35
 * @LastEditors: holylong mrhlingchen@163.com
 * @LastEditTime: 2023-08-14 16:34:59
 * @FilePath: \vcp\network\tcp_send_int_demo.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __unix__
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define closesocket close
#else
#include <windows.h>
#endif

#define SERVER_IP "127.0.0.1" //  服务器IP地址
#define SERVER_PORT 8888 // 服务器端口号

int main(int argc, char* argv[])
{
    const char *ip = SERVER_IP;
    if(argc == 2){
        ip = argv[1];        
    }

    fprintf(stdout, "ip:%s\n", ip);

    int sock; // socket descript
    struct sockaddr_in server; // server address struct
    int data = 1234; //  int number web sending
    int n; // send or recv bytes number

    // create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("socket failed");
        exit(1);
    }

    // set server address struct
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(SERVER_PORT);

    // connect server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("connect failed");
        exit(2);
    }

#if 0
    // convert int to network endian(bigendian)
    data = htonl(data);

    // send int to server
    n = send(sock, &data, sizeof(data), 0);
    if (n == -1)
    {
        perror("send failed");
        exit(3);
    }
#else
    unsigned char sendbuf[4];
    sendbuf[0] = data & 0xff;
    sendbuf[1] = (data >> 8) & 0xff;
    sendbuf[2] = (data >> 16) & 0xff;
    sendbuf[3] = (data >> 24) & 0xff;
    // send int to server
#ifdef _WIN32
    n = send(sock, (const char*)sendbuf, sizeof(sendbuf), 0);
#else
    n = send(sock, sendbuf, sizeof(sendbuf), 0);
#endif
    if (n == -1)
    {
        perror("send failed");
        exit(3);
    }
#endif 
    printf("Sent %d bytes to server\n", n);

    // close socket
    closesocket(sock);

    return 0;
}
