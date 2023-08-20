#ifndef _WSA_TIMER_H_
#define _WSA_TIMER_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <sstream>
#ifndef _WIN32
#include <sys/times.h>
#include <sys/time.h>
#else
#include <windows.h>
#endif

/**
 * @brief 根据 format 中定义的格式化规则，格式化结构 timeptr 表示的时间，并把它存储在 str 中
 * 
 * @param str  这是指向目标数组的指针，用来复制产生的 C 字符串。
 * @param maxsize 这是被复制到 str 的最大字符数。
 * @param format 这是 C 字符串，包含了普通字符和特殊格式说明符的任何组合。这些格式说明符由函数替换为表示 tm 中所指定时间的相对应值。格式说明符是：
 * @param timeptr 
 * @return size_t 
 */
// size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr);

/**
 * @brief 计算从1970年1月1号00:00（UTC）到当前的时间跨度。
 * #include <sys/time.h>
 * @param tv  
 * @param tz 
 * @return int 
 */
// int gettimeofday(struct timeval *tv, struct timezone *tz);


/**
 * @brief clock_gettime是一个Linux系统调用，用于获取当前时间。它提供了一个高精度的计时器，可以用于测量时间间隔或确定某个操作所需的时间,精度纳秒
 * #include <time.h>
 * @param clk_id CLOCK_REALTIME(), CLOCK_MONOTONIC, CLOCK_PROCESS_CPUTIME_ID,CLOCK_THREAD_CPUTIME_ID
 * @param tp 
 * @return int 
 */
// int clock_gettime(clockid_t clk_id, struct timespec *tp);


/**
 * @brief C语言的times()函数是一个标准库函数，用于获取当前系统的时间。它返回一个指向time_t类型的整数的指针，该整数表示从某个未知时刻开始经过的时钟周期数。 精度10毫秒
 * 我们首先声明一个tms结构体变量buf，然后调用times()函数将其时间信息存储在buf中。函数返回后，我们将返回值存储在time变量中，并将其打印到屏幕上。需要注意的是，times()函数已经过时，更加现代的获取系统时间的方式是使用time()函数或gettimeofday()函数。
 * #include <sys/times.h>
 * @param buf 
 * @return clock_t 
 */
// clock_t times(struct tms* buf);


/**
 * @brief 函数是C语言中的一个函数，用于获取当前的系统时间。它返回从程序启动开始经过的时钟周期数，通常是一个整数。精度10毫秒
 * 需要注意的是，clock() 函数返回的时钟周期数取决于不同的操作系统和硬件。在实际应用中，我们通常使用更为精确的计时方法，如 <chrono> 头文件中的时间函数。
 * #include <time.h>
 * @return clock_t 
 */
// clock_t clock(void);


/**
 * @brief 函数是一个计算机系统调用函数，用于获取当前的系统时间。该函数通常用于需要获取准确时间的应用程序和系统服务中。
 * typedef struct {  
    WORD wYear;  
    WORD wMonth;  
    WORD wDayOfWeek;  
    WORD wDay;  
    WORD wHour;  
    WORD wMinute;  
    WORD wSecond;  
    WORD wMilliseconds;  
} SYSTEMTIME, *PSYSTEMTIME;
 * @param s 
 */
// void GetSystemTime(SYSTEMTIME *s);

/**
 * @brief 是一个 Windows API 函数，用于获取当前本地时间的信息。它填充一个 SYSTEMTIME 结构体，其中包含了年、月、日、小时、分钟、秒和毫秒等时间信息。
 * 
 * @param s 
 */
// BOOL GetLocalTime(LPSYSTEMTIME lpSystemTime);

/**
 * @brief 函数是一个 Windows API 函数，用于将当前系统时间转换为文件时间。文件时间是指从 1601 年 1 月 1 日开始的 100 纳秒间隔的计数，用于在文件和目录中表示时间。
 * typedef struct {  
    DWORD dwLowDateTime;  
    DWORD dwHighDateTime;  
} FILETIME, *PFILETIME;
 * @param ft 
 */
// void GetSystemTimeAsFileTime(FILETIME *ft);

/**
 * @brief 函数是一个 Windows API 函数，用于获取当前系统的性能计数器的值。性能计数器是用于衡量系统、设备或应用程序性能的指标，例如 CPU 使用率、内存使用率、磁盘 I/O 速度等。
 * 其中，lpPerformanceCount 是一个指向 LARGE_INTEGER 结构体的指针，用于存储获取到的性能计数器的值。
 * LARGE_INTEGER 结构体定义如下：
 * typedef struct {  
 * DWORD LowPart;  
 * LONG HighPart; 
 * } LARGE_INTEGER, *PLARGE_INTEGER;
 * 调用 QueryPerformanceCounter 函数将会获取当前性能计数器的值，并将其存储在指定的 LARGE_INTEGER 结构体中。
 * @param lpPerformanceCount 
 * @return BOOL 
 */
// BOOL QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);


/**
 * @brief 返回编码为 std::time_t 对象的当前日历时间，并将它存储于 arg 所指向的对象，除非 arg 是空指针。
 * 定义于头文件 <ctime>

 * @param arg 
 * @return std::time_t 
 */
// std::time_t time( std::time_t* arg );

/**
 * @brief 返回编码为 std::time_t 对象的当前日历时间
 * C++11 
 * @param t 
 * @return std::time_t 
 */
//static std::time_t to_time_t( const time_point& t ) noexcept;

namespace wsa{

    enum class TIME_TYPE{
        YEAR,
        MONTH,
        DAY,
        HOUR,
        MINITE,
        SECOND,
        MILLISECOND,
        MICROSECOND,
        NANOSECOND
    };

    class WsaTimer{
        public:
            static std::string getDateTime(TIME_TYPE type = TIME_TYPE::SECOND)
            {
                std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
                std::time_t time_now = std::chrono::system_clock::to_time_t(now);
                std::tm* tm_now = std::localtime(&time_now);
                


                char buf[128] = {'0'};

                if(type == TIME_TYPE::YEAR){
                    std::strftime(buf, sizeof(buf), "%G", tm_now);
                    return std::string(buf);
                }else if(type == TIME_TYPE::MONTH){
                    std::strftime(buf, sizeof(buf), "%G-%m", tm_now);
                    return std::string(buf);
                }else if(type == TIME_TYPE::DAY){
                    std::strftime(buf, sizeof(buf), "%F", tm_now);
                    return std::string(buf);
                }else if(type == TIME_TYPE::HOUR){
                    std::strftime(buf, sizeof(buf), "%F %H", tm_now);
                    return std::string(buf);
                }else if(type == TIME_TYPE::MINITE){
                    std::strftime(buf, sizeof(buf), "%F %H %M", tm_now);
                    return std::string(buf);
                }
                std::strftime(buf, sizeof(buf), "%F %T", tm_now);

                std::stringstream ss;
                ss.fill('0');

                switch (type)
                {
                case TIME_TYPE::SECOND:
                    ss << buf;
                    break;
                case TIME_TYPE::MILLISECOND:
                    ss << buf 
                       << ":"
                       << (std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())%1000).count();
                    break;
                case TIME_TYPE::MICROSECOND:
                    ss << buf 
                       << ":"
                       << (std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())%1000).count()
                       << ":"
                       << (std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch())%1000000).count()%1000;
                    break;
                case TIME_TYPE::NANOSECOND:
                    ss << buf 
                       << ":"
                       << (std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())%1000).count()
                       << ":"
                       << (std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch())%1000000).count()%1000
                       << ":"
                       << (std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch())%1000000000).count()%1000;
                    break;
                default:
                    ss << buf;
                    break;
                }
                return ss.str();
            }

#ifdef _WIN32
            static void Test5(){
                LARGE_INTEGER start, end;  
                double elapsed;  
            
                // 获取开始时间  
                QueryPerformanceCounter(&start);  
            
                // 模拟一些处理  
                for (int i = 0; i < 1000000; i++) {  
                    // 一些处理代码...  
                }  
            
                // 获取结束时间  
                QueryPerformanceCounter(&end);  
            
                // 计算耗时（以秒为单位）  
                elapsed = (double)(end.QuadPart - start.QuadPart) / (double)QueryPerformanceFrequency(&start);  
            
                printf("Elapsed time: %.2f seconds\n", elapsed);  
            }

            static void Test6(){
                FILETIME ft;  
                GetSystemTimeAsFileTime(&ft);  
                printf("File time: %lu/%lu\n", ft.dwLowDateTime, ft.dwHighDateTime);  
            }

            static void Test7(){
                SYSTEMTIME st;  
                GetSystemTime(&st);  
                printf("Year: %d\n", st.wYear);  
                printf("Month: %d\n", st.wMonth);  
                printf("DayOfWeek: %d\n", st.wDayOfWeek);  
                printf("Day: %d\n", st.wDay);  
                printf("Hour: %d\n", st.wHour);  
                printf("Minute: %d\n", st.wMinute);  
                printf("Second: %d\n", st.wSecond);  
                printf("Milliseconds: %d\n", st.wMilliseconds);  
            }


            static void Test8(){
                SYSTEMTIME st;  
                GetLocalTime(&st);  
                printf("Year: %d\n", st.wYear);  
                printf("Month: %d\n", st.wMonth);  
                printf("DayOfWeek: %d\n", st.wDayOfWeek);  
                printf("Day: %d\n", st.wDay);  
                printf("Hour: %d\n", st.wHour);  
                printf("Minute: %d\n", st.wMinute);  
                printf("Second: %d\n", st.wSecond);  
                printf("Milliseconds: %d\n", st.wMilliseconds);  
            }
#else
            // #include <sys/time.h>
            static int Test1(){
                struct timeval val;
                int ret = gettimeofday(&val, NULL);
                if(ret == -1){
                    printf("Error: gettimeofday()\n");
                    return ret;
                }

                printf("sec:%ld, usec:%ld\n", val.tv_sec, val.tv_usec);

                return 0;
            }

            // #include <time.h>
            static void Test2(){
                struct timespec t;
                clock_gettime(CLOCK_REALTIME, &t);
                printf("now time:%ld ns\n", t.tv_nsec);
            }


            static void Test3(){
                clock_t stime, etime;
                double used_time;

                stime = clock();
                for(int i = 0; i < 100000;i++){
                    //do something
                }

                used_time = ((double)(etime-stime))/1000;
                printf("CPU use time%f\n", used_time);
            }

            static void Test4(){
                struct tms buf;
                clock_t time;
                time = times(&buf);

                printf("CPU time:%ld clock ticks\n",time); 
            }
#endif

            static void Test9(){
                std::time_t result = std::time(nullptr);
                std::cout << std::asctime(std::localtime(&result))
                        << result << " seconds since the Epoch\n";
            }

    };

#ifndef _WIN32
class timestramp{
public:
    timestramp()
    {
         gettimeofday(&tpstart,NULL);
    }

    ~timestramp()
    {
         gettimeofday(&tpend,NULL);
		 dwTime = 1000000*(tpend.tv_sec- tpstart.tv_sec)+(tpend.tv_usec- tpstart.tv_usec);
         printf("used time:%ld us\n", dwTime);
    }
private:
     struct timeval tpstart,tpend;
     double timeuse;
	 unsigned long dwTime;
};

#else

class timestramp{
private:
    LARGE_INTEGER m_litmp;
    LONGLONG QPart2;
    LONGLONG QPart1;
    double dfMinus, dfFreq, dfTim;
	static double m_dTimeCount;
public:
    timestramp(){
        QueryPerformanceFrequency(&m_litmp);
        dfFreq = (double)m_litmp.QuadPart;
        QueryPerformanceCounter(&m_litmp);
        QPart1 = m_litmp.QuadPart;
    }

    ~timestramp(){
        QueryPerformanceCounter(&m_litmp);
        QPart2 = m_litmp.QuadPart;

        //dfTim = (QPart2/dfFreq - QPart1/dfFreq)*1000*1000;
          
        dfMinus = (double)(QPart2 - QPart1);
        dfTim = dfMinus / dfFreq * 1000*1000;

        //显示时间
        std::string msg4 = "time:", msg3, msg5 = " us";
		char strTime[20] = "";
		sprintf(strTime, "%.6lf", dfTim);
		msg3 = strTime;
		msg4 += msg3;
		msg4 += msg5;
		std::cout << msg4.c_str() << std::endl;
    }
};
#endif
}

#endif //_WSA_TIMER_H_
