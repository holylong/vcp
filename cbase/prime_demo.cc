#include <iostream>
#include <vector>

bool isPrime(int x){
    if(x == 2)return true;
    for(int i = 2; i <= x/2+1; i++){
        if(x%i == 0) return false;
    }
    return true;
}

void display(const std::vector<int>& vec){
    for(auto v : vec){
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

//all 2,3,4,5,6,7,8,9
//prime 2 3 5 7
int main(int argc, char* argv[])
{
    std::vector<int> arr;
    for(int i = 2; i < 100000; i++){
        if(isPrime(i))arr.push_back(i);
    }

    display(arr);

    return 0;
}