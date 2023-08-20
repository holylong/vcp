#include <iostream>
#include "Reactor.h"
#include "SocketHandler.h"

int main(int argc, char* argv[])
{
    #ifdef _WIN32
    Win32Initialer initialer;
    #endif
    Reactor reactor;
    EventHandler *handler = reinterpret_cast<EventHandler*>(new SocketHandler(8899));
    reactor.register_handler(handler);
    reactor.handle_events();

    reactor.remove_handler(handler);
    return 0;
}