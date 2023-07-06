#include <iostream>

int main(int argc, char* argv[])
{
 std::cout << "/*";
 std::cout << std::endl;
 std::cout << "*/";
 std::cout << std::endl;
 //std::cout << /*"*/"*/;
 std::cout << /*"*/"/*"/*"*/;
 std::cout << std::endl;
 return 0;
}
