/*
 * @Author: holylong mrhlingchen@163.com
 * @Date: 2023-07-28 10:21:32
 * @LastEditors: holylong mrhlingchen@163.com
 * @LastEditTime: 2023-07-31 15:43:02
 * @FilePath: \vcp\cbase\cpu_rate.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <chrono>
#include <iostream>

#if 0
int main(int argc, char* argv[])
{
	while(1)
	{
		int i = 0;
		for(;i<100;i++)
		{};
		usleep(5000);
	}
/**
	goto Loop;
	int i = 0;
	for(;i<100;i++)
	{};
	sleep(50);
	goto Loop;
**/
	return 0;
}
#elif 0
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/time.h>  
  
#define CORES 8   // CPU 核数  
#define THRESHhold 50   // 使用率阈值，50%  
  
int main() {  
    struct timeval start, end;  
    long elapsed_time, total_time, core_time;  
  
    // 获取 CPU 核数  
    int num_cores = CORES;  
  
    // 获取总 CPU 时间  
    gettimeofday(&start, NULL);  
    elapsed_time = 0;  
    while (1) {  
        core_time = 0;  
        // 让进程在每个核上运行一段时间，控制使用率  
        for (int i = 0; i < num_cores; i++) {  
            sleep(1);  // 休眠一段时间，让进程运行  
            gettimeofday(&end, NULL);  
            elapsed_time += (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;  
            core_time += (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;  
            gettimeofday(&start, NULL);  
        }  
        // 如果使用率达到阈值，退出循环  
        if (core_time >= THRESHhold * elapsed_time) {  
            break;  
        }  
    }  
  
    // 计算总运行时间  
    gettimeofday(&end, NULL);  
    total_time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;  
  
    // 输出结果  
    printf("CPU 使用率: %.2f%%\n", core_time * 100.0 / total_time);  
  
    return 0;  
}
#else

#define INTERVAL 100 // in milliseconds

int main()
{
#ifdef _WIN32
#if 0
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::milliseconds ms;
	std::chrono::microseconds cs;
	std::chrono::nanoseconds ns;
    ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
	cs = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;
	ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()) % 1000000000;
#endif
    LARGE_INTEGER StartingTime, EndingTime;
    LARGE_INTEGER Frequency = {0};

    // 获取计数器频率
    QueryPerformanceFrequency(&Frequency);
    
    // 获取起始时间
    QueryPerformanceCounter(&StartingTime);

    std::cout << "query time" << std::endl;

    while (true) {
        while (true) {
            // Activity to be timed
            QueryPerformanceCounter(&EndingTime);

            // 计算时间间间隔，精确到微妙
            // LARGE_INTEGER ElapsedMicroseconds;
            // ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
            // ElapsedMicroseconds.QuadPart *= 1000000;
            // ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
            // if(ElapsedMicroseconds.QuadPart/1000 >= INTERVAL/2)
            //     break;
            auto elapsed = (EndingTime.QuadPart - StartingTime.QuadPart)*1000000/Frequency.QuadPart;

            if(elapsed/1000 >= INTERVAL/2)
                break;

            std::cout << "step" << std::endl;
        }
        Sleep(INTERVAL/2);
        QueryPerformanceCounter(&StartingTime);

        std::cout << "loop" << std::endl;
    }
#else
    // get the current time in nanoseconds
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    // loop until the program is terminated wq
    while (1)
    {
        // do some work for 50% of the interval
        while (1)
        {
            // get the current time in nanoseconds
            clock_gettime(CLOCK_MONOTONIC, &end);
            // check if 50% of the interval has passed convert milliseconds  ms
            if ( (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000 >= INTERVAL / 2 )
            {
                break;
            }
        }
        // sleep for the remaining 50% of the interval
        usleep(INTERVAL / 2 * 1000);
        // update the start time for the next iteration
        clock_gettime(CLOCK_MONOTONIC, &start);
    }

#endif
    return 0;
}

#endif