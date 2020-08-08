#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int tam;
	srand(time(0));
	scanf("%d",&tam);
	printf("%d \n", tam);
	for (int i = 0; i < tam; ++i)
	{
		printf("%d ", rand() % (tam*10));
	}
	printf("\n");
	return 0;
}