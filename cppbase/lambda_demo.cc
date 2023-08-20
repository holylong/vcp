/*
 * @Author: holylong mrhlingchen@163.com
 * @Date: 2023-08-14 14:23:35
 * @LastEditors: holylong mrhlingchen@163.com
 * @LastEditTime: 2023-08-14 14:43:31
 * @FilePath: \vcp\cppbase\lambda_demo.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>

void testLambda()
{
    int v = 19;
    auto f1 = [v]{return v;}; 
    auto f2 = [=]{return v;};
    auto f3 = [&v]{return v;};
    auto f4 = [&]{return v;};  

    v = 10;

    std::cout << f1() << " " << f2()  << " " << f3() << " " << f4() << std::endl;
}

int main(int argc, char* argv[])
{
    testLambda();
    return 0;
}