#include <windows.h>
#include <stdio.h>

LARGE_INTEGER PerformanceCountPerSecond;

double GetPerformanceCount()  
{  
    LARGE_INTEGER PerformanceCount;  
    QueryPerformanceCounter(&PerformanceCount);  
    return (double)PerformanceCount.QuadPart / (double)PerformanceCountPerSecond.QuadPart;  
}

void MyFunction()  
{  
    // LARGE_INTEGER StartCount, EndCount;  
    double StartTime, EndTime;  
  
    // QueryPerformanceCounter(&StartCount);  
    StartTime = GetPerformanceCount();  
  
    // 执行需要计时的代码  
  
    // QueryPerformanceCounter(&EndCount);  
    EndTime = GetPerformanceCount();  
  
    double ElapsedTime = (EndTime - StartTime) * 1000 * 1000; // 将秒转换为微秒  
    printf("MyFunction use time:%f us\n", ElapsedTime);  
}

int main(int argc, char* argv[])
{
    QueryPerformanceFrequency(&PerformanceCountPerSecond);
    MyFunction();
    return 0;
}