/*
 * @Author: holylong mrhlingchen@163.com
 * @Date: 2023-06-28 16:47:00
 * @LastEditors: holylong mrhlingchen@163.com
 * @LastEditTime: 2023-08-02 14:20:25
 * @FilePath: \vcp\network\tcp_server_demo.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
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

		void OnDisconnected(const std::string& host)
		{
			std::cout << "host:" << host.c_str() << std::endl;
		}
};

int main(int argc, char* argv[])
{
#ifdef _WIN32
	WinSockInitial initial;
#endif
	TcpSocketServer sock(9898);
	std::shared_ptr<TcpSocketListener> listener = std::make_shared<TcpSocketListener>();
	sock.SetCallback(listener);
	sock.Loop();
	return 0;
}
