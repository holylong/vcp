#include <iostream>


namespace vcp{
    class OperatorOverride{
        public:
            OperatorOverride(){}
            // 运算符重载
            // 返回值类型 operator 运算符 （形参类型）{}
            OperatorOverride& operator = (const OperatorOverride &oo);
            
    };
}


int main()
{
    return 0;
}