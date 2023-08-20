/*
 * @Author: holylong mrhlingchen@163.com
 * @Date: 2023-08-13 15:31:15
 * @LastEditors: holylong mrhlingchen@163.com
 * @LastEditTime: 2023-08-14 20:03:50
 * @FilePath: \vcp\algorithm\quick_sort.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <vector>

void display(const std::vector<int>& vec)
{
	for(auto v: vec)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;
}

// 1 5 3 7
// 0 3, 1
// 1 5 3 7
// 1 3, 1
// 1 2, 1
// 1 3 5 7
// 2 1,1
//----------------left
// 1 3 5 7
// 0 1, 0
//----------------right
// 1 3 5 7
// 0 3, 1
void quick_sort(std::vector<int>& vec, int left, int right)
{
	if(left >= right)return;

	int mid = vec[(left + right)/2];
	int i = left;
	int j = right;
	while(i < j)
	{
		display(vec);
		std::cout << i << " " << j << " " << (left + right)/2 << std::endl;
		while(vec[i] < mid && i < j)i++;
		while(vec[j] > mid && i < j)j--;
		std::cout << i << " " << j << " " << (left + right)/2 << std::endl;
		if(i < j)
		{
			vec[i] = vec[j] + vec[i];
			vec[j] = vec[i] - vec[j];
			vec[i] = vec[i] - vec[j];

			++i;
			--j;
		}
	}
	std::cout << "left:" << left << " j:" << j << " i:" << i << " right:" << right << std::endl;;
	quick_sort(vec, left, j);
	quick_sort(vec, j+1, right);
}

/**
 * @brief quick sort
 * 
 * @param vec 
 * @param left 
 * @param right 
 */
void quick_sort_copilot(std::vector<int> &vec, int left, int right)
{
	if(left >= right)return;
	int i  = left, j = right, key = vec[left];

	while(i < j){
		while(i < j && vec[j] >= key)--j;
		vec[i] = vec[j];

		while(i < j && vec[i] <= key)++i;
		vec[j] = vec[i];
	}

	vec[i] = key;

	quick_sort_copilot(vec, left, i-1);
	quick_sort_copilot(vec, i+1, right);
}

void bubble_sort(std::vector<int>& vec)
{
	for(int i = 0; i < vec.size(); i++)
		for(int j = i; j < vec.size()-1; ++j)
		{
			if(vec[i] > vec[j])
			{
				vec[i] = vec[i] + vec[j];
				vec[j] = vec[i] - vec[j];
				vec[i] = vec[i] - vec[j];
			}
		}
}

void quick_sort(std::vector<int>& vec)
{
	int mid = 0, left = 0, right = 0;
	if(vec.size() <= 1)return;

	mid = (vec.size() + left)/2;
	right = vec.size() - 1;

	while(left < right)
	{
		while(left < mid){
			if(vec[left] > vec[mid]){
				vec[left] = vec[mid] + vec[left];
				vec[mid] = vec[left] - vec[mid];
				vec[left] = vec[left] - vec[mid];
			}
		}

		while(mid < right)
		{	
			if(vec[mid] > vec[right])
			{
				vec[mid] = vec[mid] + vec[left];
				vec[right] = vec[mid] - vec[right];
				vec[mid] = vec[mid] - vec[right];
			}
		}
	}
}

void quickSort(std::vector<int> &arr, int left, int right) {
    if (left >= right) return;
    int i = left - 1, j = right + 1, pivot = arr[(left + right) / 2];
    while (i < j) {
        do i++; while (arr[i] < pivot);
        do j--; while (arr[j] > pivot);
        if (i < j) std::swap(arr[i], arr[j]);
    }
    quickSort(arr, left, j);
    quickSort(arr, j + 1, right);
}

int main(int argc, char* argv[])
{
	std::vector<int> vec{1,2,3,4,2,6,3,9,4,0,2,9,16,10};
	// std::vector<int> vec{1, 5, 3, 7};
	//bubble_sort(vec);
	//display(vec);
	
	// quick_sort_copilot(vec, 0, vec.size()-1);
	quick_sort(vec, 0, vec.size()-1);
	// quickSort(vec, 0, vec.size()-1);
	display(vec);
	return 0;
}
