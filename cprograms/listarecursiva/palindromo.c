#include <stdio.h>
#include <string.h>
#define MAX 20

int palindromo (char str[], int n)
{
	if (str[n] != str[strlen(str)-1])
		return 0;
	if (n == strlen(str)-1)
		return 1;
	if (n > strlen(str)-1)
		return 1;
	str[strlen(str)-1] = '\0';
	return palindromo(str, n+1);
}

int main(int argc, char const *argv[])
{
	char str[MAX];
	scanf("%s", str);
	
	if (palindromo(str, 0))
		printf("sim\n");
	else
		printf("nao\n");
}

/*	raaaar \o
  	01234 5   */