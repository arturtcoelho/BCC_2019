#include <stdio.h>
#include <stdlib.h>

void print(int *v , int tam){
	for (int i = 0; i < tam; ++i)
	{
		printf("%d ", v[i]);
	}
	printf("\n");
}

void merge (int *v, int *aux, int ini, int meio, int fim){	
	int i = ini, j = meio+1, k = 0, tam = fim-ini+1;

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
	return;
}

void merge_sort (int *v, int *aux, int ini, int fim, int *turno){
	if (ini >= fim)
		return;
	*turno = !*turno;
	int meio = (ini+fim)/2;
	merge_sort(v, aux, ini, meio, turno);
	merge_sort(v, aux, meio+1, fim, turno);
	merge(turno?v:aux, turno?aux:v, ini, meio, fim);
	return;
}

int main()
{
	int tam;
	int *v, *a;
	int turno = 0;
	scanf("%d", &tam);
	v = malloc(tam * sizeof(int));
	a = malloc(tam * sizeof(int));

	for (int i = 0; i < tam; i++)
		scanf("%d",&v[i]);

	merge_sort(v, a, 0, tam-1, &turno);

	// print(turno?v:a, tam);
	int i = 0;
	while(i < tam-1 && turno?v[i]:a[i] > turno?v[i+1]:a[i+1])
	{		
		i++;
	}
	if (i == tam)
		printf("seu merda %d %d\n", v[i], v[i+1]);
	else
		printf("uhul\n");

	free(v);
	free(a);
	return 0;
}
