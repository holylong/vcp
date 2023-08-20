#include <stdio.h>
#include <string.h>
#include <string>

int main(int argc, char* argv[])
{
	const char str1[15] = "abcdefghjk";
	
	const char* type_end = strstr(str1, "hjk");	
	printf("strstr:%s\n", type_end);
	
	const char* type_end1 = strstr(str1, "fgj");	
	printf("strstr:%s\n", type_end1);

	
	std::string headers = "hwllo eoels hjk nihao areyou ok!";

	headers.assign(str1, type_end);

        printf("assign:%s\n", headers.c_str());
	
	return 0;
}
