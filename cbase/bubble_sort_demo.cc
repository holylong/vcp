#include <iostream>
#include <vector>

void BubbleSort(std::vector<int>& vec)
{
    for(int i = 0; i < vec.size(); i++){
        for(int j = i; j < vec.size()-1; j++){
            if(vec[i] > vec[j]){
                vec[i] = vec[j] + vec[i];
                vec[j] = vec[i] - vec[j];
                vec[i] = vec[i] - vec[j];
            }
        }
    }
}

void Display(const std::vector<int>& vec)
{
    for(auto v: vec){
        std::cout << v << " ";
    }
    std::cout << std::endl;
}


int main(int argc, char* argv[])
{
    std::vector<int> vec{1,5,3,8,2,9,4,8,2,5,3,8,10};
    BubbleSort(vec);
    Display(vec);
    return 0;
}