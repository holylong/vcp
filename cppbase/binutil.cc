#include <iostream>  
#include <string>  
#include <algorithm>  
#include <sstream> 
 
using namespace std;  
  
// 将一个字符转换为对应的数字  
int charToNum(char c) {  
    if (c >= '0' && c <= '9') {  
        return c - '0';  
    } else {  
        return c - 'A' + 10;  
    }  
}  
  
// 将一个数字转换为对应的字符  
char numToChar(int num) {  
    if (num >= 0 && num <= 9) {  
        return num + '0';  
    } else {  
        return num - 10 + 'A';  
    }  
}  
  
// 将一个字符串从大到小排序，用于基数为16的进制转换  
bool cmp(char a, char b) {  
    //reverse(a.begin(), a.end());  
    //reverse(b.begin(), b.end());  
    return a > b;  
}  
  
// 通用的进制转换工具  
string convertNum(int num, int base, int targetBase) {  
    string result = "";  
    stringstream ss;
    while (num > 0) {  
        int remainder = num % targetBase;  
        ss << charToNum(remainder + '0'); // 将数字转换为字符并添加到结果字符串中  
        num /= targetBase;

	//std::cout << "result:" << ss.str() << " " << num << std::endl;  
    }
    result = ss.str(); 
    //sort(result.begin(), result.end(), cmp); // 将结果字符串从大到小排序  
    reverse(result.begin(), result.end()); // 将结果字符串从小到大排序  
    return result;  
}  
// base16 ==> 0x100
// base10 ==> 256
// base8  ==> 0400
// base2  ==> 0001 0000 0000 
int main(int argc, char* argv[]) { 
    if(argc != 4){
	std::cout << "please input arguments:" << argv[0] << " " << 256 << " " << 10 << " " << 16 << std::endl; 
	return -1;
    }
 	 
    int num = atoi(argv[1]); // 要转换的数字  
    int base = atoi(argv[2]); // 数字的当前进制  
    int targetBase = atoi(argv[3]); // 数字的目标进制  
    string result = convertNum(num, base, targetBase);  
    cout << num << " in base " << base << " is " << result << " in base " << targetBase << endl;  
    return 0;  
}
