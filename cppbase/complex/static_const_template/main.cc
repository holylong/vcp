#include "options_registry.h"

int main(int argc, char* argv[])
{
    std::cout << "registration_token address:" << &complex::tool::OptionsRegistry::registration_token<MyMessage> << std::endl; // 输出一个地址
    return 0;
}