#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int lin, col;
	int **m;
} matriz;

void aloca_matriz(matriz *m){
	(m->m) = malloc(m->lin * sizeof(int*));
	for (int i = 0; i < m->lin; ++i)
	{
		*(m->m + i) = malloc(m->col * sizeof(int));
	}
	return;
}

void ler (matriz* m){
	for (int i = 0; i < m->lin; ++i)
	{
		for (int j = 0; j < m->col; ++j)
		{
			scanf("%d", &m->m[i][j]);
		}
	}
}

int calc_ij (matriz* a, matriz* b, int i, int j){
	int soma = 0;
	for (int k = 0; k < a->lin; ++k)
	{
		soma += a->m[i][k] * b->m[k][j];
	}
	return soma;
}

void multiplica (matriz* a, matriz* b, matriz* c){
	for (int i = 0; i < c->lin; ++i)
	{
		for (int j = 0; j < c->col; ++j)
		{
			c->m[i][j] = calc_ij(a, b, i, j);
		}
	}
}


int imprime (matriz* m){
	for (int i = 0; i < m->lin; ++i)
	{
		for (int j = 0; j < m->col; ++j)
		{
			printf("%d ", m->m[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	matriz a, b, c;
	scanf("%d%d%d%d", &a.lin, &a.col, &b.lin, &b.col);
	if (a.col == b.lin){
		c.lin = a.lin;
		c.col = b.col;
		aloca_matriz(&a);
		aloca_matriz(&b);
		aloca_matriz(&c);

		ler(&a);
		ler(&b);

		multiplica(&a, &b, &c);

		imprime(&c);
	}
	else
		printf("nao da\n");

	return 0;
}