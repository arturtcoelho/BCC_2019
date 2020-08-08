#include <stdio.h>
#include <stdlib.h>

void imprime (int *v, int ini, int fim){
	for (int i = ini; i < fim; ++i)
	{
		printf("%d ", v[i]);
	}
	printf("\n");
}

void troca (int *v, int i, int j){
	int aux = v[i];
	v[i] = v[j];
	v[j] = aux;
	return;
}

int partition (int *v, int ini, int fim){
	int i = ini-1, j = ini;
//	printf("%d \n", v[(ini+fim)/2]);
	troca(v, (ini+fim)/2, fim);
	int pivo = v[fim];

	// printf("%d %d\n", ini, fim);
	// printf("%d %d\n", i+1, v[i+1]);
	for (; j < fim; ++j)
	{
		if (v[j] <= pivo)
		{
			i++;
			troca(v, i, j);
		}
	}
	troca(v, i+1, fim);
//	imprime(v, ini, fim);
	return i+1; //indice do pivo;
}

void quicksort (int *v, int ini, int fim, int tam){
	if (ini >= fim)
		return;
	int meio = partition(v, ini, fim);
	// printf("%d\n", meio);
	//imprime(v, 0, tam);
	quicksort(v, ini, meio-1, tam);
	quicksort(v, meio+1, fim, tam);
}

int main()
{
	int tam, *v;
	scanf("%d", &tam);
	v = malloc(tam * sizeof(int));

	for (int i = 0; i < tam; ++i)
		scanf("%d", &v[i]);

	quicksort(v, 0, tam-1, tam);

	//imprime(v, 0, tam-1);

	int i = 0;
	while((i < tam-1) && (v[i] <= v[i+1]))
		i++;
	if (i+1 == tam)
		printf("uhull\n");
	else
		printf("fudeo\n");

	return 0;
}
