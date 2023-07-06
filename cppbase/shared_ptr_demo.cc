#include <iostream>
#include <memory>

#ifdef _WIN32
#if !defined(__PRETTY_FUNCTION__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
#endif

#define DISPLAY(tx) std::cout << __PRETTY_FUNCTION__ << " " << tx << std::endl;
#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;

template<typename T, typename V>
class Fruit{
    public:
        Fruit() = default;


        virtual void Display(const T& msg){
            DISPLAY(msg)
        }

        virtual void Display(const V& msg){
            DISPLAY(msg)
        }
};

template<typename T, typename V>
class Orange;

template<typename T, typename V>
class Apple : public Fruit<T,V>{
    public:
        Apple(std::string color, size_t size):_color(color), _size(size){
            TRACE
        }

        virtual ~Apple(){
            TRACE
        }

        void setOrange(std::shared_ptr<Orange<T,V>>& orange){
            _orange = orange;
        }

        std::string color(){
            return _color;
        }

        size_t radius(){
            return _size;
        }

        void use_count(){
            DISPLAY(_orange.use_count())
        }

    private:
        std::shared_ptr<Orange<T,V>> _orange;
        std::string _color;
        size_t      _size;
};

template<typename T, typename V>
class Orange : public Fruit<T, V>{
    public:
        Orange(std::string color, size_t size, std::string taste)
        :_color(color), _size(size), _taste(taste){
            TRACE
        }

        virtual ~Orange(){
            TRACE
        }

        void setApple(std::shared_ptr<Apple<T,V>>& apple){
            _apple = apple;
        }

        std::string color(){
            return _color;
        }

        std::string taste(){
            return _taste;
        }

        size_t      radius(){
            return _size;
        }

        void use_count(){
            DISPLAY(_apple.use_count())
        }

    private:
        std::weak_ptr<Apple<T,V>> _apple;
        // std::shared_ptr<Apple<T, V>> _apple;
        std::string    _color;
        size_t         _size;
        std::string    _taste;
};

int main(){
    std::shared_ptr<Apple<int, std::string>> apple = std::make_shared<Apple<int, std::string>>("red", 10);
    apple->Display(apple->radius());
    apple->Display(apple->color());

    std::shared_ptr<Orange<int, std::string>> orange = std::make_shared<Orange<int, std::string>>("yellow", 15, "sweetness");
    orange->Display(orange->color());
    orange->Display(orange->radius());
    orange->Display(orange->taste());

    apple->use_count();
    orange->use_count();
    std::cout << "apple:" << apple.use_count() << std::endl;
    std::cout << "orange:" << orange.use_count() << std::endl;

    //weak_ptr
    apple->setOrange(orange);
    orange->setApple(apple);

    
    apple->use_count();
    orange->use_count();
    std::cout << "apple:" << apple.use_count() << std::endl;
    std::cout << "orange:" << orange.use_count() << std::endl;

    //shared_ptr
    return 0;
}