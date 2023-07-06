#include <iostream>

#ifdef _WIN32
#if !defined(__PRETTY_FUNCTION__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
#endif

class Component{
    public:
        virtual void operation() = 0;
};

class Sprite : public Component{
    public:
        virtual void operation() override{
            std::cout << __PRETTY_FUNCTION__ << std::endl;
        }
};

class Weapon : public Component{
    protected:
        Component* _component;
    public:
        Weapon(Component* c):_component(c){}
        virtual void operation() override{
            return _component->operation();
        }
};

class Gun : public Weapon{
    public:
        Gun(Component* c):Weapon(c){}
        virtual void operation() override{
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            Weapon::operation();
        }
};

class Knife : public Weapon{
    public:
        Knife(Component* c):Weapon(c){}
        virtual void operation() override{
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            Weapon::operation();
        }
};

int main(int argc, char* argv[])
{
    Component* sprite = new Sprite();
    Weapon* knife = new Knife(sprite);
    knife->operation();

    Weapon* gun = new Gun(sprite);
    gun->operation();


    return 0;
}