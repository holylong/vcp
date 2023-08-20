#include <WsaTimer.h>

int main(int argc, char* argv[])
{
    {
        wsa::timestramp ti;
    
        std::cout << "now:" << wsa::WsaTimer::getDateTime(wsa::TIME_TYPE::YEAR) << std::endl;
        std::cout << "now:" << wsa::WsaTimer::getDateTime(wsa::TIME_TYPE::MONTH) << std::endl;
        std::cout << "now:" << wsa::WsaTimer::getDateTime(wsa::TIME_TYPE::DAY) << std::endl;
        std::cout << "now:" << wsa::WsaTimer::getDateTime(wsa::TIME_TYPE::HOUR) << std::endl;
        std::cout << "now:" << wsa::WsaTimer::getDateTime(wsa::TIME_TYPE::MINITE) << std::endl;
        std::cout << "now:" << wsa::WsaTimer::getDateTime() << std::endl;
        std::cout << "now:" << wsa::WsaTimer::getDateTime(wsa::TIME_TYPE::MILLISECOND) << std::endl;
        std::cout << "now:" << wsa::WsaTimer::getDateTime(wsa::TIME_TYPE::MICROSECOND) << std::endl;
        std::cout << "now:" << wsa::WsaTimer::getDateTime(wsa::TIME_TYPE::NANOSECOND) << std::endl;
    }
    return 0;
}