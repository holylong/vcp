#ifndef _BASE_SOCKET_H_
#define _BASE_SOCKET_H_

#include <iostream>

#ifdef _WIN32

#else
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <memory>
#include <arpa/inet.h>
#endif

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
                TcpSocketServer(int port){
                    Init();
                    Bind(port);
                    Listen();
                }

                void SetCallback(const std::shared_ptr<SocketListner>& listener){
                    _listener = listener;
                }

                void Accept(){
                    std::cout << "wait client..." << std::endl;
                    while(!_stop){
                        struct sockaddr_in cliaddr;
                        int clifd = accept(_sockfd, (struct sockaddr*)&cliaddr, NULL);
                        char buffer[1024] = {0}; 
                        inet_ntop(AF_INET, &(cliaddr.sin_addr), buffer, sizeof(buffer));

                        _listener->OnConnected(clifd, buffer);
                        WanSleep(1);
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
                SOCKET _sockfd;
            #else
                int    _sockfd;
            #endif
                bool   _stop{false};


                std::shared_ptr<SocketListner> _listener;

                void Init(){
                    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
                    if(_sockfd < 0){
                        std::cerr << "Error: Could not create socket." << std::endl;
                        exit(1);
                    }
                }

                void Bind(int port){
                    struct sockaddr_in seraddr;
                    seraddr.sin_family = AF_INET;
                    seraddr.sin_port = htons(port);
                    seraddr.sin_addr.s_addr = INADDR_ANY;
                    if(bind(_sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr)) < 0){
                        std::cerr << "Error: Could not bind socket." << std::endl;
                        exit(1); 
                    }
                }

                void Listen(){
                    if(listen(_sockfd, 10) < 0){
                        std::cerr << "Error: Could not listen on socket." << std::endl;
                        exit(1);
                    }
                }
        };
    }
}

#endif //_BASE_SOCKET_H_