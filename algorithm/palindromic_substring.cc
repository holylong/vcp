#include <iostream>

std::string findMaxPalindromicSubString(const std::string& s)
{
    int max = 0;
    int maxi = 0, maxj = 0;
    for(int i = 0; i < s.length()-i; i++){
        for(int j = i; j < s.length(); ++j){
            if(i != j && s.at(i) == s.at(j)){
                if((j-i) > max){
                    max = j-i;
                    maxi = i;
                    maxj = j;
                }
                std::cout << i << "-" << j << " " << s.substr(i, max) << std::endl;
                break;
            }        
        }
    }

    std::cout << maxj << " " << maxi << " " << max << std::endl;
    if(max == 0)return s;
    return s.substr(maxi, max);
}

//i j
//i = 0 j = 0
int main(int argc, char* argv[])
{
    std::string str = "abcdefghjklmnsafhsdfhfjahfjhfsjfjshjfhasjf";
    std::string linstr = findMaxPalindromicSubString(str);
    std::cout << linstr << std::endl;
}