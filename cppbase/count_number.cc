#include <iostream>

int main()
{
	int curVal = 0, val = 0;
        if(std::cin >> curVal){
		int cnt = 1;
            while(std::cin >> val){
			if(val == curVal)
				cnt++;
			else{
				std::cout << "val:" << curVal << " has:" <<cnt << std::endl;
                                curVal = val;
				cnt = 1;
			}
		}
				std::cout << "val:" << curVal << " has:" <<cnt << std::endl;
	}  
	return 0;
}
