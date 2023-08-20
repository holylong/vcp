/*
 * @Author: holylong mrhlingchen@163.com
 * @Date: 2023-08-03 16:12:23
 * @LastEditors: holylong mrhlingchen@163.com
 * @LastEditTime: 2023-08-03 17:08:11
 * @FilePath: \vcp\network\reactor\SocketHandler.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// SocketHandler.cpp
#include "SocketHandler.h"
#include <iostream>

#ifndef _WIN32
#include <errno.h>
#endif

#include <string.h>

SocketHandler::SocketHandler(int port) {
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        fprintf(stderr, "socket error:%d", listen_fd);
        exit(1);
    }
    int opt = 1;
#ifdef _WIN32
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
#else
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        #ifdef _WIN32
        fprintf(stderr, "bind error:%d", GetLastError());
        #else
        fprintf(stderr, "bind error:%d", errno);
        #endif
        exit(1);
    }
    if (listen(listen_fd, 5) < 0) {
        perror("listen error");
        exit(1);
    }else{
        fprintf(stdout, "server listen:%d\n", port);
    }
    conn_fd = -1;
}

SocketHandler::~SocketHandler() {
    closesocket(listen_fd);
    closesocket(conn_fd);
}

int SocketHandler::get_handle() {
    return listen_fd;
}

void SocketHandler::handle_read() {
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    conn_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &len);
    if (conn_fd < 0) {
        perror("accept error");
        return;
    }
    std::cout << "Accepted a new connection from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;
    // 创建一个新的SocketHandler对象，用于处理该连接的读写事件
    SocketHandler* handler = new SocketHandler(conn_fd);
}

void SocketHandler::handle_write() {
    char buffer[1024];
    sprintf(buffer, "Hello, this is a message from server.\n");
    int n = send(conn_fd, buffer, strlen(buffer), 0);
    if (n < 0) {
        perror("send error");
        return;
    }
}

void SocketHandler::handle_close() {
    closesocket(conn_fd);
}