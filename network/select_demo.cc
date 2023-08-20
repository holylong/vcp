#include <iostream>

#include<stdio.h>
#include<stdlib.h>

#ifdef _WIN32
#include <windows.h>

// #include <base.h>
#else
#include<unistd.h>
#include<arpa/inet.h>
#endif

#include<string.h>
#include<ctype.h>

#define SERV_PORT 9909

int clientCount(int* arr, int leng){
   int count = 0;
   for(int i = 0; i < leng; i++){
      if(arr[i] !=-1)count++;
   }
   return count;
}

int main(int argc, char* argv[])
{
  int i,j,n,maxi=-1;

#ifdef _WIN32
   WSADATA  wsaData;
   WSAStartup(MAKEWORD(2,2), &wsaData);
   int maxfd;
   SOCKET listenfd,connfd,sockfd;
#else
  int maxfd,listenfd,connfd,sockfd;
#endif

  /// FD_SETSIZE=1024,定义数组client来储存已连接描述符，最多1023个

  int nready = -1, clients[FD_SETSIZE-1];  
#ifdef _WIN32
   char buf[BUFSIZ];
#else
   char buf[BUFSIZ], str[16];
#endif

  struct sockaddr_in clie_addr,serv_addr;
#ifdef _WIN32
   int clie_addr_len;
#else
  socklen_t clie_addr_len;
#endif

  //定义监听描述符集合allset和发生事件描述符集合readset
  fd_set allset,readset;  
#ifdef _WIN32
   memset(&serv_addr, 0, sizeof(serv_addr));
#else
  bzero(&serv_addr, sizeof(serv_addr));
#endif

   serv_addr.sin_family = AF_INET;
   //端口号，将无符号短整型转换为网络字节顺序
   serv_addr.sin_port = htons(SERV_PORT);

   //一个主机可能有多个网卡，所以是本机的任意IP地址
#ifdef _WIN32
   serv_addr.sin_addr.S_un.S_addr = INADDR_ANY;
#else
   serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  
#endif
   //AF_INET表示使用32位IP地址，SOCK_STREAM表示使用TCP连接
   listenfd = socket(AF_INET,SOCK_STREAM,0); 

   int opt = 1;
#ifdef _WIN32
   if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt))) {
#else
   if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
#endif
     std::cerr << "Error: setting socket options failed" << std::endl;
     return 1;
   }

  if(bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0){
      std::cerr << "Error: socket binding failed" <<  std::endl;
      return 1;
  }
  
  if(listen(listenfd,1024) != 0){
   std::cerr << "Error: socket listening failed" << std::endl;
   return 1;
  }else{
   std::cout << "Success: socket listening on:" << SERV_PORT << std::endl;
  }

 /// 初始化最大文件描述符为监听描述符listenfd
 maxfd = listenfd; 
 for(i=0;i<FD_SETSIZE;i++)
   clients[i]=-1;

  //初始化select监听文件描述符的集合
  FD_ZERO(&allset);     //初始化监听集合
  FD_SET(listenfd,&allset);  //将监听描述符listenfd添加到集合中
  
  while(1)
  {
    readset=allset;
	/// select只监听可读事件，且为永久阻塞直到有事件发生
    nready = select(maxfd+1,&readset,NULL,NULL,NULL);

    if (nready<0)
       std::cerr << "select error" << std::endl;

    /// 判断listenfd是否发生事件，若发生，则处理新客户端连接请求
    if (FD_ISSET(listenfd, &readset))
    {
       clie_addr_len = sizeof(clie_addr);
       /// 与请求客户端建立连接
       connfd = accept(listenfd,(struct sockaddr *)&clie_addr,&clie_addr_len);
       /// 打印该客户端的IP地址和端口号
#ifdef _WIN32
         printf("received from %s at port %d\n", inet_ntoa(clie_addr.sin_addr), ntohs(clie_addr.sin_port));  
#else
         printf("received from %s at port %d\n", inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr, str, sizeof(str)), ntohs(clie_addr.sin_port));  
#endif
           
      //将connfd赋值给client数组中第一个为-1的元素位置
      for (i=0;i<FD_SETSIZE;i++)
      {
         if (clients[i]<0)
         {
            clients[i] = connfd;
            break;
         }
      }
 
      //判断select监听的文件描述符的个数是否超过上限
      if (i == FD_SETSIZE-1)   //减1的原因是要考虑监听描述符listenfd也属于select监控
      {
         fputs("too many clients\n",stderr);
         exit(1);
      }

      FD_SET(connfd,&allset);  //向监控的文件描述符集合allset中添加新的描述符connfd
      if (connfd>maxfd)
         maxfd=connfd;   //更新最大文件描述符值
  
      //保证maxi永远是client数组中最后一个非-1的元素的位置
      if(i>maxi)
         maxi=i;

      fprintf(stdout, "new client connect...\n");

      fprintf(stdout, "client number:%d\n", clientCount(clients, FD_SETSIZE));

      //如果nready=1，即只有一个发生事件的描述符，在此条件下必为listenfd，则返回循环位置，继续调用select监控；否则继续向下执行
      --nready;
      if (nready==0)
          continue;
    }

    /// 找到client数组中发生事件的已连接描述符，并读取、处理数据
    for (i=0;i<=maxi;i++)
    {
        sockfd = clients[i];
       if (sockfd<0)  //已连接描述符失效，重新开始循环
          continue;  
        
       if (FD_ISSET(sockfd,&readset))
       {
#ifdef _WIN32
            n = recv(sockfd, buf, sizeof(buf), 0);
#else
            n = read(sockfd,buf,sizeof(buf));
#endif
          if (n==0) //当客户端关闭连接，服务端也关闭连接
          {
#ifdef _WIN32
             closesocket(sockfd); 
#else
             close(sockfd);
#endif
             FD_CLR(sockfd,&allset);  //解除select对该已连接文件描述符的监控
             clients[i]=-1;

             fprintf(stdout, "client number:%d\n", clientCount(clients, FD_SETSIZE));
          }
          else if (n>0)
          {
            fprintf(stdout, "recv from client %d : %s", sockfd, buf);
            for (j=0;j<n;j++)
                buf[j]=toupper(buf[j]);
#ifdef _WIN32
               Sleep(2);
               send(sockfd,buf,n,0);
#else
               usleep(2000);
               write(sockfd,buf,n);
#endif
          }

          --nready;
          if (nready==0)
              break;  //跳出for循环，还在while中
       }
    }
  }
#ifdef _WIN32
    closesocket(listenfd);
    WSACleanup();
#else
    close(listenfd);
#endif
  return 0;
} 
