#include<stdio.h>
#include<string.h>

int main()
{
	 char haystack[20] = "RUNOOB";
	 char needle[10] = "OOB";
	char* ret = strstr(haystack, needle);

	printf("Õ·×ª·´²à£º%s\n", ret);
	
	return(0);
}