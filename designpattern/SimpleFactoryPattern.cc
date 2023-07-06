// simple factory pattern
#include <iostream>

class SimpleFactory{
public:
    virtual ~SimpleFactory(){}
    virtual void operation() = 0;
};

class ConcreteSimpleFactory : public SimpleFactory{
public:
    void operation() override{
        std::cout << "ConcreteSimpleFactory::operation()" << std::endl;
    }
};

int main(int argc, char* argv[]){
    
}