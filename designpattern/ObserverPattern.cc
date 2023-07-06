#include <iostream>
#include <vector>

#ifdef _WIN32
#if !defined(__PRETTY_FUNCTION__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
#endif

class Subject;

class Observer{
    public:
        virtual void update(Subject* subject) = 0;

    protected:
        std::string _title;
};

class Subject{
    public:
        void attach(Observer* observer){
            _observers.push_back(observer);
        }

        void detach(Observer* observer){
            for(auto iter = _observers.begin();
                iter != _observers.end(); ++iter)
                {
                    if(*iter == observer){
                        _observers.erase(iter);
                        break;
                    }
                }
        }

        void notify(){
            for(auto observer : _observers){
                observer->update(this);
            }
        }

    private:
        std::vector<Observer*> _observers;
};

class ConcreteObserver : public Observer{
    public:
        ConcreteObserver(const std::string & title){
            _title = title;
        }
        void update(Subject* subject) override{
            std::cout << __PRETTY_FUNCTION__  << " " << _title.c_str() << " update observer" << std::endl;
        }
};

int main(int argc, char* argv[])
{
    Subject subject;

    ConcreteObserver observer("dog"), observer2("cat");

    subject.attach(&observer);
    subject.attach(&observer2);

    subject.notify();

    subject.detach(&observer);
    subject.detach(&observer2);

    return 0;
}