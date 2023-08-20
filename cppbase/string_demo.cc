#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
	std::string request_headers = "helllo worlld! Are You Ok! This is Beijing China!";
        std::string result_headers  = "";
	const int len = 5;
        size_t found = request_headers.find("!");
	if(found != std::string::npos){
	    result_headers = request_headers.substr(found + len);
            request_headers.resize(found + len);

           std::cout << "substr:" << result_headers.c_str() << "== resize:" << request_headers.c_str() << std::endl;
	}
	return 0;
} 
