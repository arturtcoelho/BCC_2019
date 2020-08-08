#include <stdio.h>

int fatorial (int n)
{
	if (n == 0) return 1;
	return (n*fatorial(n-1));
}

int combinacao (int m, int p)
{
	return (fatorial(m) / (fatorial(p) * fatorial(m-p)));
}

void linha_R (int linha, int n)
{
	if (n > linha)
	{
		printf("\n");
		return;
	}
	printf("%d ", combinacao(linha, n));
	linha_R(linha, n+1);
}

void triangulo_R (int n)
{
	if (n == 0) 
	{
		printf("1\n");	
		return;
	}
	triangulo_R(n-1);
	linha_R(n, 0);
	return;
}

int main()
{
	int n;
	scanf("%d", &n);
	triangulo_R(n);
	return 0;
}