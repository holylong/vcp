#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <arpa/inet.h>
#endif
#include <string.h>
#include <iostream>  
  
void checkEndian() {  
    int num = 1;  
    if (*(char *)&num == 1) {  
        std::cout << "Little-Endian" << std::endl;  
    } else {  
        std::cout << "Big-Endian" << std::endl;  
    }
}

void checkEndian1(){
		int x = 0x1234;
		if(*(char*)&x == 0x12){
			std::cout << "Big-Endian" << std::endl;  
		}else{
			std::cout << "Little-Endian" << std::endl;  
		}
} 

int convertEndian() {  
    unsigned int num = 0x12345678; // 32位整数，假设为大端字节序  
    unsigned char bytes[4];  
    memcpy(bytes, &num, sizeof(num)); // 将num的字节拷贝到bytes数组中  
    if (bytes[0] == 0x12 && bytes[1] == 0x34 && bytes[2] == 0x56 && bytes[3] == 0x78) {  
        std::cout << "Big-Endian" << std::endl;  
        unsigned int converted_num = (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0]; // 转换为大端字节序  
        std::cout << "Converted: " << std::hex << converted_num << std::endl;  
    } else {  
        std::cout << "Little-Endian" << std::endl;  
        unsigned int converted_num = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3]; // 转换为小端字节序  
        std::cout << "Converted: " << std::hex << converted_num << std::endl;  
    }  
    return 0;  
}

int convertEndian1(){
		 unsigned int num = 0x12345678;
	  unsigned int dst = (num&0xff) << 24|
		  									(num&0xff00) << 8|
		  									(num&0xff0000) >> 8|
		  								  (num&0xff000000) >> 24;
		std::cout << "Origin:" << std::hex << num << " "
			<< "Converted:" << std::hex << dst << " "
			<< "htonl:" << std::hex << htonl(num) << std::endl;

            return 0;
}

// 大端转小端

// 小端转大端
void ts_little_to_big_endian(){
    int x = 0x12345678;
    int y = (x & 0xff) << 24 | (x &0xff00) << 8 | (x & 0xff0000) >> 8 | (x & 0xff000000) >> 24;

    printf("%x %x %x\n", x, y, htonl(x));
}

// 主机与网络数据互相转换

/**
 * @brief test
 * 
 * @param argc 
 * @param argvp 
 * @return int 
 */
int main(int argc, char* argvp[])
{
    checkEndian();
    checkEndian1();
    convertEndian();
    convertEndian1();
    ts_little_to_big_endian();
    return 0;
    
}