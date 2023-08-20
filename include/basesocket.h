#ifndef _BASE_SOCKET_H_
#define _BASE_SOCKET_H_

#ifdef _WIN32

#else
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <memory>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#endif
#include <iostream>
#include <sstream>
#include "base.h"

namespace wanda {
    namespace net {
        class SocketListner{
            public:
                virtual void OnConnected(const WanSocket &sock, const std::string& host) = 0;
                virtual void OnRecv(const std::string& bf) = 0;
                virtual void OnDisconnected(const std::string& host) = 0; 
        };


        class TcpSocketClient{
            public:
                TcpSocketClient();
                ~TcpSocketClient();


                void Init(){
                    _sock = socket(AF_INET, SOCK_STREAM, 0);
                #ifdef _WIN32
                    if(_sock == INVALID_SOCKET){
                #else
                    if(_sock < 0){
                #endif
                        std::cerr << "Error: init socket failed." << std::endl;
                        exit(-1);
                    }
                }

                bool Connect(const std::string& host, const int port)
                {
                    struct sockaddr_in addr;
                    addr.sin_family = AF_INET;
                    addr.sin_port = htons(port);
                    addr.sin_addr.s_addr = inet_addr(host.c_str());
#ifdef _WIN32
                    if (connect(_sock, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR){
#else
                    if (connect(_sock, (struct sockaddr*)&addr, sizeof(addr)) <= 0){
#endif
                        std::cerr << "Error: connect failed." << std::endl;
                        exit(-1);
                    }
                    return true;
                }
                bool IsConnected() const
                {
                    #ifdef _WIN32
                        return _sock != INVALID_SOCKET;
                    #elif defined(__linux__)
                        return _sock > 0;
                    #endif
                }

                void Close();

                void SetSocketListner(SocketListner *s){
                    _listener = s;
                }
                SocketListner *GetSocketListner() const;

                bool Send(const std::string& data){
                    #ifdef _WIN32
                        return ::send(_sock, data.c_str(), data.length(), 0) > 0;
                    #else
                        return ::write(_sock, data.c_str(), data.length()) > 0;
                    #endif
                }
                std::string Recv();

                void SetRecvTimeOut(const int sec);
                int GetRecvTimeOut() const;

                void SetSendTimeOut(const int sec);
                int GetSendTimeOut() const;

                void SetRecvBuffSize(const int size);
                int GetRecvBuffSize() const;

            private:
                #ifdef _WIN32
                WanSocket _sock{INVALID_SOCKET};
                #else
                WanSocket _sock{-1};
                #endif
                SocketListner *_listener;
        };

        class TcpSocketServer{
            public:
                // TcpSocket(const std::string& host, int port){
                TcpSocketServer(int port):_stop(false){
                    Init();
                    Bind(port);
                    Listen();
                }

                void SetCallback(const std::shared_ptr<SocketListner>& listener){
                    _listener = listener;
                }

                void SetNonBlocking(){
                    #ifdef _WIN32
                    unsigned long flag = 1;
                    if(ioctlsocket(_listenfd, FIONBIO, &flag) == SOCKET_ERROR){
                    #else
                    int cflags = fcntl(_listenfd, F_GETFL, 0); 
                    if(fcntl(_listenfd, F_SETFL, cflags | O_NONBLOCK) == -1){
                    #endif
                        std::cerr << "ioctlsocket set non blocking error" << std::endl;
                        exit(-1);
                    }
                }

                void SetBlocking(){
                    #ifdef _WIN32
                    unsigned long flag = 0;
                    if(ioctlsocket(_listenfd, FIONBIO, &flag) == SOCKET_ERROR){
                    #else
                    int cflags = fcntl(_listenfd, F_GETFL, 0); 
                    if(fcntl(_listenfd, F_SETFL, cflags & ~O_NONBLOCK) == -1){
                    #endif
                        std::cerr << "ioctlsocket set non blocking error" << std::endl;
                        exit(-1);
                    }
                }

                void SetReuseAddr(){
                    // Set the socket options
                    int opt = 1;
                    #ifdef _WIN32
                    if (setsockopt(_listenfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt))) {
                    #else
                    if (setsockopt(_listenfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
                    #endif
                        std::cerr << "Error: setting socket options failed" << std::endl;
                        exit(-2);
                    }
                }

                void Loop(){
                    std::cout << "wait client..." << std::endl;
                    while(!_stop){
                        struct sockaddr_in cliaddr;
                        int clifd = accept(_listenfd, (struct sockaddr*)&cliaddr, NULL);
                        char buffer[1024] = {0}; 
                        inet_ntop(AF_INET, &(cliaddr.sin_addr), buffer, sizeof(buffer));

                        _listener->OnConnected(clifd, buffer);
                        WanSleep(1);
                    }
                }

            private:
                void Select(){
                    int clisocks[FD_SETSIZE] = {0};
                    fd_set max_fds;
                    FD_ZERO(&max_fds);
                    FD_SET(_listenfd, &max_fds);
                    int maxfd = _listenfd;
                    fd_set cp_fds = max_fds;

                    if(select(maxfd+1, &max_fds, NULL, NULL, NULL) < 0){
                        std::cerr << "select event error" << std::endl;
                        exit(-1);
                    }

                    for(int i = 0; i < maxfd; i++){
                        int clisock = clisocks[i];
                        if(FD_ISSET(clisock, &cp_fds)){

                        }
                    }

                    if(FD_ISSET(_listenfd, &cp_fds)){

                    }
                }

                void Send(const WanSocket& clifd, const std::string& msg){
                    #ifdef _WIN32
                        ::send(clifd, msg.c_str(), msg.length(), 1);
                    #else
                        ::write(clifd, msg.c_str(), msg.length());
                    #endif
                }

                void Quit(){
                    _stop = true;
                }

            private:
            #if _WIN32
                SOCKET _listenfd;
            #else
                int    _listenfd;
            #endif
                bool   _stop{false};


                std::shared_ptr<SocketListner> _listener;

                void Init(){
                    _listenfd = socket(AF_INET, SOCK_STREAM, 0);
                    if(_listenfd < 0){
                        std::cerr << "Error: Could not create socket." << std::endl;
                        exit(1);
                    }
                }

                void Bind(int port){
                    struct sockaddr_in seraddr;
                    seraddr.sin_family = AF_INET;
                    seraddr.sin_port = htons(port);
                    seraddr.sin_addr.s_addr = INADDR_ANY;
                    if(bind(_listenfd, (struct sockaddr*)&seraddr, sizeof(seraddr)) < 0){
                        std::cerr << "Error: Could not bind socket." << std::endl;
                        exit(1); 
                    }
                }

                void Listen(){
                    if(listen(_listenfd, 10) < 0){
                        std::cerr << "Error: Could not listen on socket." << std::endl;
                        exit(1);
                    }
                }
        };

        class SocketUtil{
            //获取本地连接地址
            static std::string getSocketIpAddrStr(int sockfd){
                socklen_t addrLen;
                struct sockaddr_in skAddr;
                if(getsockname(sockfd, (struct sockaddr*)&skAddr, &addrLen) == -1){
                    return std::string("");
                }

                std::stringstream ss;
                ss << inet_ntoa(skAddr.sin_addr);
                ss << ":";
                ss << ntohs(skAddr.sin_port);

                return ss.str();
            }

            static std::string getPeerIpAddrStr(int sockfd){
                socklen_t addrLen;
                struct sockaddr_in skAddr;
                if(getpeername(sockfd, (struct sockaddr*)&skAddr, &addrLen) == -1){
                    return std::string("");
                }

                std::stringstream ss;
                char buf[16] = {0};
                ss << inet_ntop(AF_INET, &skAddr.sin_addr, buf, sizeof(buf));
                ss << ":";
                ss << ntohs(skAddr.sin_port);

                return ss.str();
            }
        };
#ifdef _WIN32
        class WinSockInitial{
            public:
                WinSockInitial(){
                    WSAData data{};
                    WSAStartup(MAKEWORD(2,2), &data);
                }

                virtual ~WinSockInitial(){
                    WSACleanup();
                }
        };
#endif
    }
}

#endif //_BASE_SOCKET_H_