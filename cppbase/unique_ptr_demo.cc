#include <iostream>
#include <memory>

#ifdef _WIN32
#if !defined(__PRETTY_FUNCTION__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
#endif

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;

class App{
public:
    App() = default;
    App(int a, int b){

    }

    void runOver(){
        TRACE
    }
};

class Device{
public:
    Device() = default;
    Device(int a, int b) = delete;
    Device(std::unique_ptr<App> app) = delete;

    virtual void Display() = 0;
    virtual void Play() = 0;
    virtual void runOver() = 0;

    std::unique_ptr<App> getApp(){return std::move(_app);}
protected:
    std::unique_ptr<App> _app;
};

class Tv : public Device{
public:
    Tv(int a, int b){
        _app = std::make_unique<App>(a, b);
    }

    Tv(std::unique_ptr<App> app){
        _app = std::move(app);
    }

    void Display(){
        TRACE
    }

    void Play(){
        TRACE
    }

    void runOver(){
        _app->runOver();
    }
};

class Phone : public Device{
public:
    Phone(int a, int b){
        _app = std::make_unique<App>(a, b);
    }
    Phone(std::unique_ptr<App> app){
        _app = std::move(app);
    }
    void Play(){
        TRACE
    }

    void Display(){
        TRACE
    }

    void runOver(){
        _app->runOver();
    }
};


int main(int argc, char* argv[])
{
    int a = 0, b =100;
    Tv tv(a, b);

    std::unique_ptr<App> pt(new App(a,b));
    Phone phone(std::move(pt));

    tv.Display();
    tv.Play();
    tv.getApp()->runOver();
    tv.runOver();

    phone.Display();
    phone.Play();
    phone.getApp()->runOver();
    phone.runOver();
}