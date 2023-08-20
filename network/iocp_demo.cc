#include <iostream>
#include <WinSock2.h>
#include <windows.h>

#include <thread>
#include <vector>

std::atomic_bool isShutdown = false;
SOCKET serverSocket = INVALID_SOCKET;
HANDLE iocpHandle = INVALID_HANDLE_VALUE;
constexpr static size_t MaxBufferSize = 1024*1;
constexpr static size_t NumberOfThreads = 1;

std::vector<std::thread> threadGroup;

enum class IOType{
    Read,
    Write
};

typedef struct{
    OVERLAPPED overlapped{};
    SOCKET socket = INVALID_SOCKET;
    DWORD nBytes = 0;
    IOType type{};
    CHAR buffer[MaxBufferSize]{};
    WSABUF wsaBuff{MaxBufferSize, buffer};
}IOContext;

void AcceptWorkerThread(){
    while(!isShutdown){
        // 开始监听接入
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if(INVALID_SOCKET == clientSocket)continue;

        // 将接入的套接字也设置为非阻塞的
        unsigned long ul = 1;
        if(SOCKET_ERROR == ioctlsocket(clientSocket, FIONBIO, &ul)){
            shutdown(clientSocket, SD_BOTH);
            closesocket(clientSocket);
            continue;
        }

        // 此处不创建IOCP,将套接字绑定到现有的IOCP上
        if(nullptr == CreateIoCompletionPort((HANDLE)clientSocket, iocpHandle, 0, 0)){
            shutdown(clientSocket, SD_BOTH);
            closesocket(clientSocket);
            continue;
        }

        DWORD nBytes = MaxBufferSize;
        DWORD dwFlags = 0;
        auto ioContext = new IOContext;
        ioContext->socket = clientSocket;
        ioContext->type = IOType::Read;

        auto rt = WSARecv(clientSocket, &ioContext->wsaBuff, 1, &nBytes, &dwFlags, &ioContext->overlapped, nullptr);
        auto err = WSAGetLastError();
        if(SOCKET_ERROR == rt && ERROR_IO_PENDING != err){
            shutdown(clientSocket, SD_BOTH);
            closesocket(clientSocket);
            delete ioContext;
        }
    }
}

void EventWorkerThread(){
    IOContext *ioContext = nullptr;
    DWORD lpNumberOfBytesTransferred = 0;
    void *lpCompletionKey = nullptr;

    DWORD dwFlags = 0;
    DWORD nBytes = MaxBufferSize;

    while(true){
        BOOL bRt = GetQueuedCompletionStatus(iocpHandle, &lpNumberOfBytesTransferred, 
                                (PULONG_PTR)&lpCompletionKey, (LPOVERLAPPED*)&ioContext, INFINITE);
        if(!bRt)continue;

        // 收到PostQueuedCompletionStatus 发出的退出指令
        if(lpNumberOfBytesTransferred == -1)break;
        if(lpNumberOfBytesTransferred == 0)continue;

        // 读到或者写入的字节数
        ioContext->nBytes = lpNumberOfBytesTransferred;

        // 处理对应的事件
        switch (ioContext->type){
            case IOType::Read:{
                int nRt = WSARecv(ioContext->socket, &ioContext->wsaBuff, 1, &nBytes, &dwFlags, &(ioContext->overlapped), nullptr);
                auto e = WSAGetLastError();
                if(SOCKET_ERROR == nRt && e != WSAGetLastError()){
                    closesocket(ioContext->socket);
                    delete ioContext;
                    ioContext = nullptr;
                }else{
                    setbuf(stdout, nullptr);
                    puts(ioContext->buffer);
                    fflush(stdout);
                    closesocket(ioContext->socket);
                    delete ioContext;
                    ioContext = nullptr;
                }
                break;
            }
            case IOType::Write:{
                break;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    WSAData data{};
    WSAStartup(MAKEWORD(2,2), &data);

    struct sockaddr_in address = {};
    address.sin_family = AF_INET;
    address.sin_port = htons(9909);
    address.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    // inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

    // 初始化Socket
    unsigned long ul = 1;
    serverSocket = WSASocketW(AF_INET, SOCK_STREAM, 0, nullptr, 0, WSA_FLAG_OVERLAPPED);
    if(INVALID_SOCKET == serverSocket){
        perror("FAILED TO CREATE SERVER SOCKET");
        closesocket(serverSocket);
        return -1;
    }

    // 设置为非阻塞IO
    if(SOCKET_ERROR == ioctlsocket(serverSocket, FIONBIO, &ul)){
        perror("FAILED TO SET NONBLOCKING SOCKET");
        closesocket(serverSocket);
        return -2;
    }

    // 绑定端口
    if(SOCKET_ERROR == bind(serverSocket, (const struct sockaddr*)&address, sizeof(address))){
        perror("FAILED TO BIND ADDRESS");
        closesocket(serverSocket);
        return -3;
    }

    // 监听端口
    if(SOCKET_ERROR == listen(serverSocket, SOMAXCONN)){
        perror("FAILED TO LISTEN SOCKET");
        closesocket(serverSocket);
        return -4;
    }

    // 创建IOCP内核对象并获取句柄
    /*****************************************************************************/
    // FileHandle 一个已经打开的文件句柄，
    // ExistingCompletionPort 一个已经存在的IOCP句柄
    // CompletionKey 完成键
    // NumberOfConcurrentThreads 并发使用的线程数量，此参数限定并发线程的上限，而不是所有线程池的上限
    iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, NumberOfThreads);
    if(INVALID_HANDLE_VALUE == iocpHandle){
        perror("FAILED TO CREATE IOCP HANDLE");
        closesocket(serverSocket);
        return -5;
    }

    // 基本的对象都创建完成，需要启动工作线程计入连接并进行处理
    for(size_t i = 0; i < NumberOfThreads; i++){
        threadGroup.emplace_back(std::thread(EventWorkerThread));
    }

    void *lpCompletionKey = nullptr;
    auto acceptThread = std::thread(AcceptWorkerThread);
    getchar();
    isShutdown = true;

    // 有多少线程post多少次，让工作线程收到事件并主动退出
    for(size_t i = 0; i < NumberOfThreads; i++){
        PostQueuedCompletionStatus(iocpHandle, -1, (ULONG_PTR)lpCompletionKey, nullptr);
    }

    acceptThread.join();
    for(auto &thread:threadGroup){
        thread.join();
    }

    WSACleanup();
    return 0;
}