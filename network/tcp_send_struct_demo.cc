/*
 * @Author: holylong mrhlingchen@163.com
 * @Date: 2023-08-14 14:16:25
 * @LastEditors: holylong mrhlingchen@163.com
 * @LastEditTime: 2023-08-14 16:10:28
 * @FilePath: \vcp\network\tcp_send_struct_demo.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifdef __unix__
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#define closesocket close
#elif defined(_WIN32)
#include <windows.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8866

struct Person {
  char name[100];
  int age;
};

// client
int main(int argc, char* argv[]) {

  const char* ip = SERVER_IP;
  if(argc == 2){
    ip = argv[1];
  }
  fprintf(stdout, "ip:%s\n", ip);

  // create socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("socket");
    exit(1);
  }

  // connect server
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_addr(ip);
  if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("connect");
    exit(1);
  }

  // init struct
  struct Person person;
  strcpy(person.name, "John Doe");
  person.age = 30;

//   convert byte endian
//   htonl(person.age);

  // send struct
#ifdef _WIN32
  int n = send(sockfd, (const char*)&person, sizeof(person), 0);
#else
  int n = send(sockfd, &person, sizeof(person), 0);
#endif
  if (n < 0) {
    perror("send");
    exit(1);
  }

  // close socket
  closesocket(sockfd);

  return 0;
}