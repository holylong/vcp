#include <iostream>
#include <map>
#include <iterator>

#include <tracer.h>

class ConfigManager{
  public:
  static ConfigManager* Instance(){
    static ConfigManager manager;
    return &manager;
  }

  std::string getValue(const std::string & key) const{
    std::map<std::string, std::string>::const_iterator iter;
    if((iter = _kvs.find(key)) != _kvs.end()){
      return iter->second;
    }
    return nullptr;
  } 

  void setValue(const std::string & key, const std::string & t){
    _kvs[key] = t;
  }

  void Display(const std::string & key){
    std::map<std::string, std::string>::const_iterator iter;
    if((iter = _kvs.find(key)) != _kvs.end()){
      WSA_TRACE(iter->second.c_str());
    }
  }

  private:
    std::map<std::string, std::string> _kvs;
};

int main(int argc, char* argv[])
{
  ConfigManager::Instance()->setValue("path", "skyer/ddb");

  ConfigManager::Instance()->setValue("path2", "skyer/ddb2");

  ConfigManager::Instance()->Display("path2");
  return 0;
}
