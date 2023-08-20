/*
 * @Author: holylong mrhlingchen@163.com
 * @Date: 2023-08-11 20:52:11
 * @LastEditors: holylong mrhlingchen@163.com
 * @LastEditTime: 2023-08-13 19:49:46
 * @FilePath: \vcp\cbase\yiyan_cpu_rate.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>  
#ifdef __unix__
#include <unistd.h>

#define MySleep(x) usleep(x*1000)
#else
#include <winsock2.h>

#define MySleep(x) Sleep(x)
#endif
#include <time.h>
#include <stdlib.h>

int main()  
{  
    const int CPU_AFFINITY = 0;  // 将进程绑定到CPU核心0  
    const int TARGET_USAGE = 50; // 目标CPU使用率  
    const int INTERVAL = 1000000; // 采样间隔（微秒）  
    long long count = 0; // 计数器  
    long long total_time = 0; // 总时间  
    long long start_time, end_time; // 记录开始和结束时间  
    int cpu_usage; // CPU使用率  
  
    while (1) {  
        // 将进程绑定到CPU核心0  
        printf("Binding to CPU core %d\n", CPU_AFFINITY);  
        system("taskset -c 0 ./build_ninja/cbase/yiyan_cpu_rate");  
  
        // 记录开始时间  
        start_time = clock();  
  
        // 循环，控制CPU使用率  
        for (int i = 0; i < INTERVAL; i++) {  
            // 空循环，让CPU占用时间  
            while (count < TARGET_USAGE) {  
                count++;  
            }  
            count = 0;  
            // 休眠一段时间，控制CPU使用率  
            MySleep(1);  
        }  
  
        // 记录结束时间  
        end_time = clock();  
        total_time += (end_time - start_time);  
  
        // 计算CPU使用率  
        cpu_usage = (int)(100 * (double)INTERVAL / (double)total_time);  
        printf("CPU usage: %d%%\n", cpu_usage);  
    }  
    return 0;  
}
