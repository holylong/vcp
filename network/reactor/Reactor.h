/*
 * @Author: holylong mrhlingchen@163.com
 * @Date: 2023-08-03 16:10:41
 * @LastEditors: holylong mrhlingchen@163.com
 * @LastEditTime: 2023-08-03 16:51:11
 * @FilePath: \vcp\network\reactor\Reactor.h
 */

#ifndef _REACTOR_H_
#define _REACTOR_H_

#ifdef _WIN32
  #include <winsock2.h>
  typedef int socklen_t;
  typedef SOCKET NativeSocket;
#else
    #include <sys/select.h>
  #define closesocket close
  typedef int NativeSocket;
#endif

#include <vector>
#include <map>
#ifdef _WIN32
class Win32Initialer{
    public:
        Win32Initialer(){
            WSAData wsa;
            WSAStartup(MAKEWORD(2,2), &wsa);
        }

        virtual ~Win32Initialer(){
            WSACleanup();
        }
};
#endif
class EventHandler {
public:
    virtual int get_handle() = 0; // 获取socket文件描述符
    virtual void handle_read() = 0; // 处理读事件
    virtual void handle_write() = 0; // 处理写事件
    virtual void handle_close() = 0; // 处理关闭事件
};

class Reactor {
public:
    Reactor();
    ~Reactor();
    void register_handler(EventHandler* handler); // 注册事件处理器
    void remove_handler(EventHandler* handler); // 移除事件处理器
    void handle_events(); // 处理事件循环

private:
    int max_fd; // 最大的文件描述符
    fd_set read_set; // 读集合
    fd_set write_set; // 写集合
    std::map<int, EventHandler*> handlers; // 文件描述符和事件处理器的映射
};

#endif //_REACTOR_H_