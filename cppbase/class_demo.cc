#include <iostream>

class DataProcessor{
    public:
        std::string name() const { return name_; }
        void setName(const std::string& name) { name_ = name; }

        bool isHasName(const std::string& name){
            return name == name_;
        }

        void Display(const std::string& name){
            std::cout << "name:" << name.c_str() << std::endl; 
        }

    private:
        std::string name_;
};

int main(int argc, char* argv[])
{
    DataProcessor processor;
    processor.setName("UglyGirl");

    if(processor.isHasName("UglyMan")){
        processor.Display("true");
    }else{
        processor.Display("false");
    }

    if(processor.isHasName("UglyGirl")){
        processor.Display("true");
    }else{
        processor.Display("false");
    }
    return 0;
}