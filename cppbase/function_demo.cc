#include <iostream>
#include <memory>
#include <functional> // for std::function and std::bind

class Sprite{
    public:
        Sprite() = default;
        typedef std::function<int(int, int)> PlusFunction;


        void registerPlusSignal(const PlusFunction& callback){
            _callback = callback;
        }

        int plusSignal(int a, int b){
            return _callback(a,b);
        }

    private:
        PlusFunction _callback;
};

class Idle{
    public:
        Idle(){
            // _sprite = std::make_shared<Sprite>();
        }
        void registerCallback(const Sprite::PlusFunction& callback){
            if(_sprite.get() == nullptr){
                std::cout << " Must Set Sprite Before RegisterCallback" << std::endl;
                return;
            }
            _sprite->registerPlusSignal(callback);
        }


        int Plus(int a, int b){
            return a+b;
        }

        void setSprite(std::shared_ptr<Sprite>& sprite){
            _sprite = sprite;
        }


        std::shared_ptr<Sprite> _sprite;
};

int main() {
    //function demo
    Idle idle;
    std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
    idle.setSprite(sprite);
    idle.registerCallback(std::bind(&Idle::Plus, &idle, std::placeholders::_1, std::placeholders::_2));

    int a = 0, b = 0;
    while(a != 10000){
        std::cout << "please input two number" << std::endl;
        std::cin >> a >> b;
        std::cout << "the plus " << a << " + " << b <<  " result:" << sprite->plusSignal(a, b) << std::endl;
    }

    //other exp
    int x = 42;
    auto addOneFunc = [](auto& arg) -> decltype(arg + 1) { return arg + 1; };
    
    auto resultAddOne = std::bind(addOneFunc, std::forward<decltype(x)>(x));
    
    if (resultAddOne() == 43) {
        std::cout << "Success!" << resultAddOne() << std::endl;
    } else {
        std::cout << "Error, result was " << resultAddOne() << std::endl;
    }
}