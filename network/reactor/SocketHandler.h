// SocketHandler.h

#ifndef _SOCKET_HANDLER_H_
#define _SOCKET_HANDLER_H_

#include "Reactor.h"
#ifdef _WIN32
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif 

class SocketHandler : public EventHandler {
public:
    SocketHandler(int port); // 构造函数，创建并绑定socket
    ~SocketHandler(); // 析构函数，关闭socket
    int get_handle(); // 获取socket文件描述符
    void handle_read(); // 处理读事件，接受客户端连接，并创建新的SocketHandler对象
    void handle_write(); // 处理写事件，发送数据给客户端
    void handle_close(); // 处理关闭事件，关闭连接

private:
    NativeSocket listen_fd; // 监听socket文件描述符
    NativeSocket conn_fd; // 连接socket文件描述符
};

#endif //_SOCKET_HANDLER_H_