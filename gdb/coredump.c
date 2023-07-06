	#include<stdio.h>
	int coredump_next()
	{
			int *ptr = NULL;
		  *ptr = 101;
		  return 0;
	}
	
	int coredump(){
			return coredump_next();
	}
	
	int main()
	{
		return coredump();
	}
