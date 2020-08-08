#include <stdio.h>
#include <stdlib.h>

void print(int *v , int tam){
	for (int i = 0; i < tam; ++i)
	{
		printf("%d ", v[i]);
	}
	printf("\n");
}

void merge (int *v, int ini, int meio, int fim){	
	int i = ini, j = meio+1, k = 0, tam = fim-ini+1;
	int *aux = malloc(tam * sizeof(int));
	if (aux == NULL)
	{
		printf("fudeo\n");
		exit(1);
	}

	while(i <= meio && j <= fim)
	{
		if (v[i] < v[j]){
			aux[k] = v[i];
			i++;
		}
		else{
			aux[k] = v[j];
			j++;
		}
		k++;
	}

	while(i <= meio)
	{
		aux[k] = v[i];
		k++;
		i++;
	}

	while(j <= fim)
	{
		aux[k] = v[j];
		k++;
		j++;
	}

	for (int i = ini; i <= fim; ++i)
	{
		v[i] = aux[i-ini];
	}
	free(aux);
	return;
}

void merge_sort (int v[], int ini, int fim){
	if (ini >= fim)
		return;
	int meio = (ini+fim)/2;
	merge_sort(v, ini, meio);
	merge_sort(v, meio+1, fim);
	merge(v, ini, meio, fim);
	return;
}



int main()
{
	int tam;
	int *v;
	scanf("%d", &tam);
	v = malloc(tam * sizeof(int));

	for (int i = 0; i < tam; i++)
	{
		scanf("%d",&v[i]);
	}

	merge_sort(v, 0, tam-1);

//	print(v, tam);
	int i = 0;
	while(i < tam-1 && v[i] > v[i+1])
	{		
		i++;
	}
	if (i == tam)
		printf("seu merda %d %d\n", v[i], v[i+1]);
	else
		printf("uhul\n");


	printf("\n");

	return 0;
}
