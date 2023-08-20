/*
 * @Author: holylong mrhlingchen@163.com
 * @Date: 2023-08-09 15:35:23
 * @LastEditors: holylong mrhlingchen@163.com
 * @LastEditTime: 2023-08-14 16:29:39
 * @FilePath: \vcp\network\tcp_recv_struct_demo.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __unix__
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define closesocket close
#else
#include <windows.h>
#endif

#define PORT 8866

// struct define
struct Person {
  char name[100];
  int age;
};

// server end
int main() {
  // create socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("socket");
    exit(1);
  }

  // socket bind port 
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(1);
  }

  // listen socket
  if (listen(sockfd, 10) < 0) {
    perror("listen");
    exit(1);
  }

  // wait connection
  int clientfd = accept(sockfd, NULL, NULL);
  if (clientfd < 0) {
    perror("accept");
    exit(1);
  }

  // recv struct
  struct Person person;
#ifdef _WIN32
  int n = recv(clientfd, (char*)&person, sizeof(person), 0);
#else
  int n = recv(clientfd, &person, sizeof(person), 0);
#endif
  if (n < 0) {
    perror("recv");
    exit(1);
  }

  //  convert byte endian
//   ntohl(person.age);

  // display struct
  printf("Name: %s\n", person.name);
  printf("Age: %d\n", person.age);

  //  closesocket
  closesocket(clientfd);
  closesocket(sockfd);

  return 0;
}