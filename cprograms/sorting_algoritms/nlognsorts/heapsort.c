#include <stdio.h>
#include <stdlib.h>

int esquerda(int i){
	return 2*i +1;
}

int direita(int i){
	return 2*i +2;
}

int pai(int i){
	return (i-1)/2;
}

void troca(int *v, int a, int b){
	int aux = v[a];
	v[a] = v[b];
	v[b] = aux;
	return;
}

/*
	5
  4	  3
 2 1 0 -1
// */

// int largest = i; // Initialize largest as root 
//     int l = 2*i + 1; // left = 2*i + 1 
//     int r = 2*i + 2; // right = 2*i + 2 
  
//     // If left child is larger than root 
//     if (l < n && arr[l] > arr[largest]) 
//         largest = l; 
  
//     // If right child is larger than largest so far 
//     if (r < n && arr[r] > arr[largest]) 
//         largest = r; 

void max_heapfy(int *v, int tam, int i){
	int maior = i;

	if (esquerda(i) < tam && v[maior] < v[esquerda(i)])
		maior = esquerda(i);

	if (direita(i) < tam && v[maior] < v[direita(i)])
		maior = direita(i);

	if (maior == i)
		return;
	// else
	troca(v, maior, i);
	max_heapfy(v, tam, maior);
	return;
}

void construct_max_heapfy(int *v, int tam){
	for (int i = tam/2; i >= 0; --i)
	{
		max_heapfy(v, tam, i);
	}
}

void heap_sort(int *v, int tam){
	construct_max_heapfy(v, tam);
	int tam_o = tam;
	for (int i = tam-1; i >= 0; --i)
	{
		troca(v, 0, i);
		max_heapfy(v, i, 0);
	}
}

int main()
{
	int *v, tam;
	scanf("%d", &tam);
	v = (int*)malloc(tam*sizeof(int));

	for (int i = 0; i < tam; ++i)
		scanf("%d", v+i);

	heap_sort(v, tam);

	for (int i = 0; i < tam; ++i)
		printf("%d ", v[i]);
	printf("\n");

	return 0;
}