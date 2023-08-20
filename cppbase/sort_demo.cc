#include <iostream>
#include <algorithm>
#include <vector>

// 从大到小排列
bool cmp(int a, int b){
	return a > b;
}

// 从小到大排列
bool rcmp(int a, int b){
	return a < b;
}

#define ARRAYSIZE(a) sizeof(a)/sizeof(a[0])

int main(int argc, char* argv[])
{
	int a[] = {1,5,3,8,6,9,10, 100,45,67};

	std::sort(a, a+10, rcmp);

	for(int i = 0; i < ARRAYSIZE(a); i++)
		std::cout << a[i] << " ";
	std::cout << std::endl;


	std::vector<int> arr = {1,4,6,7,8,3,100,10000,4,6,32,65,78,65,32};
	std::sort(arr.begin(), arr.end(), rcmp);
	for(int i = 0; i < arr.size(); i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
	
	
	return 0;
}
