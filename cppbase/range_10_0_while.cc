#include <iostream>

int main(int argc, char* argv[])
{
  int start = 10, end = 0;
  while(start > 0){
	  std::cout << start-- << " ";
  }
  std::cout << std::endl;
  return 0;
}
