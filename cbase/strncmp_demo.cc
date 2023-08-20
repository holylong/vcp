#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
  char str1[15] = {0};
  char str2[15] = {0};
  int ret = -1;

  strcpy(str1, "abcdef");
  strcpy(str2, "ABCDEF");

  ret = strncmp(str1, str2, 4);
  if(ret < 0) printf("str1 smaller than str2\n");
  else if(ret > 0) printf("str1 larger than str2\n");
  else printf("str1 equal with str2\n");
   
  return 0;
}
