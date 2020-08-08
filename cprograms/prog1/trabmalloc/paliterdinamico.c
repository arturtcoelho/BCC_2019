#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	char *str = NULL, *pal = NULL, ch = EOF;
	int i, j, tam = 0;

/*leitura e alocacao dinamica em str* (tam)*/
	ch = getc(stdin);
	while (ch != '\n' && ch != ' ' && ch != EOF)
	{
		str = realloc(str, tam+1 * sizeof(char));
		if (str != NULL)
		{
			*(str+tam) = ch;
			tam++;
			ch = getc(stdin);
		}
		else
			exit(1);
	}

/*formacao do palindromo*/
	pal = malloc(tam * sizeof(char));
	for (i = 0, j = tam; i < tam; ++i, --j)
	{
		*(pal+i) = *(str+j-1);
	}	

/*calculo do palindromo*/
	i = 0;
	while ((*(pal+i) == *(str+i)) && i < tam)
	{
		i++;
	}

	if (i == tam)
		printf("eh\n");
	else
		printf("num eh\n");

	return 0;
}