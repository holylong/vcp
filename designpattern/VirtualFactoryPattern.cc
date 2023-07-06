//factory method pattern

#include <iostream>

class Fruit{
public:
    virtual ~Fruit(){}
    virtual void color() = 0;
};

class Apple : public Fruit{
public:
    void color() override{
        std::cout << "Apple::pink" << std::endl;
    }
};

class Orange : public Fruit{
public:
    void color() override{
        std::cout << "Orange::yellow" << std::endl;
    }
};

class Vegetable{
    public:
        virtual~Vegetable(){}
        virtual void size() = 0;
};

class Cucumber : public Vegetable{
    public:
    void size() override{
        std::cout << "12px" << std::endl;
    }
};

class Tomato : public Vegetable{
    public:
        void size() override{
            std::cout << "10px" << std::endl;
        }
};

class Factory{
public:
    virtual ~Factory(){}
    virtual Fruit* createFruit() = 0;
    virtual Vegetable* createVegetable() = 0;
};

class FactoryA : public Factory{
    public:
        Fruit* createFruit(){
            return new Apple();
        }

        Vegetable* createVegetable(){
            return new Cucumber();
        }
};

class FacotryB : public Factory{
    public:
        Fruit* createFruit(){
            return new Orange();
        }

        Vegetable* createVegetable(){
            return new Tomato();
        }
};

int main(int argc, char* argv[]){
    Factory* factory1 = new FactoryA();
    Fruit* apple = factory1->createFruit();
    Vegetable* cucumber = factory1->createVegetable();

    apple->color();
    cucumber->size();


    delete factory1;
    delete apple;
    delete cucumber;

    Factory* factory2 = new FacotryB();
    Fruit* orange = factory2->createFruit();
    Vegetable* tomato = factory2->createVegetable();
    orange->color();
    tomato->size();

    delete factory2;
    delete orange;
    delete tomato;
}