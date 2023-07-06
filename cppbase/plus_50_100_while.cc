#include <iostream>

int main(int argc, char* argv[])
{ 
  int start = 50, end = 100, val = 0;
  while(start < end){
	val += start;
        ++start;
  }
  std::cout << "range from 50 to 100 number sum is:" << val << std::endl;
  return 0;
}
