#include <iostream>

int main(int argc, char* argv[])
{
	int start, end;
	if(argc < 3)
	{
	  std::cout << "please input two numbers" << std::endl;
	  std::cin >> start >> end;	
	}else
           start = atoi(argv[1]), end = atoi(argv[2]);
        if(start > end)
	{
		start += end;
		end = start - end;
                start -= end;
	}
        int i = start;
	for(;i < end;){
        //for(int i = start; i < end; i++){
		std::cout << i++ << " ";
	}
	std::cout << std::endl;
	return 0;
}
