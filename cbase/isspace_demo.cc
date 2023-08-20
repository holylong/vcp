#include <stdio.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
	int var1 = 't';
	int var2 = '1';
        int var3 = ' ';

	if(isspace(var1))printf("var1 = |%c| is black char\n", var1);
	else printf("var1 = |%c| is not black char\n", var1);
	if(isspace(var2))printf("var1 = |%c| is black char\n", var2);
	else printf("var1 = |%c| is not black char\n", var2);
	if(isspace(var3))printf("var1 = |%c| is black char\n", var3);
	else printf("var1 = |%c| is not black char\n", var3);
      return 0; 
}
