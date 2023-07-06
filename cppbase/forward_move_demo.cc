#include <iostream>

#ifdef _WIN32
#if !defined(__PRETTY_FUNCTION__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
#endif

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;

class ByteDance{
    public:
        ByteDance() = delete;
        ByteDance(const char* locale):_location(locale){
            TRACE
        }
        ByteDance(const std::string& locale):_location(locale){
            TRACE
        }
        ByteDance(std::string && locale):_location(locale){
            TRACE
        }

    private:
        std::string _location;
};

template <typename T>
ByteDance* createCompany(T t){
    return new ByteDance(t);
}

template <typename T>
ByteDance* createCompany2(T& t){
    return new ByteDance(t);
}

template <typename T>
ByteDance* createCompany3(T&& t){
    return new ByteDance(t);
}

template <typename T>
ByteDance* createCompany4(T&& t){
    return new ByteDance(std::forward<T>(t));
}

void forwardLoop(){
    std::string locale1 = "BeiJing";
    std::string locale2 = "ShangHai";
    const char* locale3 =  "ShenZhen";
    ByteDance* btDance1 = createCompany(locale1);
    ByteDance* btDance2 = createCompany(locale2 + locale1);
    ByteDance* btDance3 = createCompany(locale3);
}

void forwardLoop2(){
    std::string locale1 = "BeiJing";
    std::string locale2 = "ShangHai";
    const char* locale3 =  "ShenZhen";
    ByteDance* btDance1 = createCompany2(locale1);
    // ByteDance* btDance2 = createCompany2(locale2 + locale1);
    ByteDance* btDance3 = createCompany2(locale3);
}

void forwardLoop3(){
    std::string locale1 = "BeiJing";
    std::string locale2 = "ShangHai";
    const char* locale3 =  "ShenZhen";
    ByteDance* btDance1 = createCompany3(locale1);
    ByteDance* btDance2 = createCompany3(locale2 + locale1);
    ByteDance* btDance3 = createCompany3(locale3);
}

void forwardLoop4(){
    std::string locale1 = "BeiJing";
    std::string locale2 = "ShangHai";
    const char* locale3 =  "ShenZhen";
    ByteDance* btDance1 = createCompany4(locale1);
    ByteDance* btDance2 = createCompany4(locale2 + locale1);
    // ByteDance* btDance3 = createCompany5(locale3);
}


int main(int argc, char* argv[])
{
    std::cout << "===========值传递===========" << std::endl;
    forwardLoop();
    std::cout << "===========左值引用传递===========" << std::endl;
    forwardLoop2();
    std::cout << "===========右值引用传递, 无法成功调用右值引用构造函数===========" << std::endl;
    forwardLoop3();

    std::cout << "===========右值引用传递, 成功调用右值引用构造函数===========" << std::endl;
    forwardLoop4();
}
