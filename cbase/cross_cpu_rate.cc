/*
 * @Author: holylong mrhlingchen@163.com
 * @Date: 2023-08-11 16:08:44
 * @LastEditors: holylong mrhlingchen@163.com
 * @LastEditTime: 2023-08-13 19:51:34
 * @FilePath: \vcp\cbase\cross_cpu_rate.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <chrono>
#ifdef __unix__
#include <unistd.h>
#define MySleep(x) usleep(x*1000)
#elif defined(_WIN32)
#include <Windows.h>
#define MySleep(x) Sleep(x)
#endif 
#define PERCENT_NUM 100

int main(int argc, char* argv[])
{
    std::chrono::milliseconds start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())%1000;
    std::chrono::milliseconds end;
    while(true){
        
        while(true){
             end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())%1000;
            if( (end.count() - start.count()) >= PERCENT_NUM/2){
                break;
            }
        }

        MySleep(PERCENT_NUM/2);
        start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())%1000;
    }
    return 0;
}