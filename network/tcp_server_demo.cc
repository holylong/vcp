#include <iostream>

#include <basesocket.h>

using namespace wanda::net;

class TcpSocketListener : public SocketListner {
	public:
		void OnConnected(const WanSocket &sock, const std::string& host){
			std::cout << "sock:" << sock << " host:" << host.c_str() << std::endl;
		}

		void OnRecv(const std::string& msg){
			std::cout << "msg:" << msg.c_str() << std::endl;
		}
};

int main(int argc, char* argv[])
{
	TcpSocketServer sock(9898);
	sock.Accept();
	return 0;
}
