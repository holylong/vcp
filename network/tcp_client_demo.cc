#include <iostream>

#include<stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#include <stdlib.h>
#include <string.h>

#define SERV_IP "172.19.0.213"
#define SERV_PORT 9909

int main(int argc, char* argv[])
{
#ifdef _WIN32
   WSADATA wsaData;
   WSAStartup( MAKEWORD( 2, 2 ), &wsaData);
   SOCKET cfd;
#else
   int cfd;
#endif
   struct sockaddr_in serv_addr;
   char buf[BUFSIZ];
   int n;

   char* ddr = const_cast<char*>(SERV_IP);

   if(argc >  1){
      ddr = argv[1];
   }

   cfd=socket(AF_INET,SOCK_STREAM,0);
   
   memset(&serv_addr,0,sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(SERV_PORT);
   
   //将点十进制字节串转换为网络字节序
#ifdef _WIN32
   serv_addr.sin_addr.S_un.S_addr = inet_addr(ddr);
#else
   inet_pton(AF_INET, ddr, &serv_addr.sin_addr.s_addr);  
#endif

   int ret = connect(cfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
   if(ret < 0){
      std::cerr << "Connection failed.\n";
      return -1;
   }



   while(1)
   {
      std::cout << "wait for input..." << std::endl;
      fgets(buf,sizeof(buf),stdin);
#ifdef _WIN32
      send(cfd, buf, strlen(buf), 0);
      n = recv(cfd, buf, sizeof(buf), 0);
      fprintf(stdout, buf, n, 0);
#else
      write(cfd,buf,strlen(buf));
      n=read(cfd,buf,sizeof(buf));
      write(STDOUT_FILENO,buf,n);
#endif
   }
#ifdef _WIN32
   closesocket(cfd);
   WSACleanup();
#else
   close(cfd);
#endif
   return 0;
}
