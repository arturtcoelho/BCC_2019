#include <stdio.h>
#include <string.h>
#define MAX 20


int main(int argc, char const *argv[])
{
	char str[MAX];
	scanf("%s", str);
	if (str[0] == str[strlen(str)-1])		
	printf("%ld\n", strlen(str));
	printf("%s\n", str);
	return 0;
}