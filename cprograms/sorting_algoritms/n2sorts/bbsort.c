#include <stdio.h>

int main()
{
	int tam, a, troca = 1;
	scanf("%d\n", &tam);
	int v[tam];

	//leitura

	for (int i = 1; i<=tam; i++)
		scanf("%d", &v[i]);
	
	//bubble sort
	while (troca) {
		troca = 0;
		for (int i = 1; i < tam; i++) {
			if (v[i]>v[i+1]) {
				a = v[i];
				v[i] = v[i+1];
				v[i+1] = a;
				troca++;
			}
		}
	}

	//impressao
	/*
	for (int i = 1; i <=tam; i++)
		printf("%d ", v[i]);
	printf(" \n");
	*/
	return 0;
}