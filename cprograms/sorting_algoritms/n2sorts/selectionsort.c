#include <stdio.h>

int main()
{
	int v[100], tam, maior;

	//leitura
	scanf("%d", &tam);
	for (int i = 0; i < tam; i++)
		scanf("%d", &v[i]);
	
	//selection sort
	for (int i = 0; i < tam; ++i) {
		maior = v[i]; 
		for (int j = i+1; i < tam; ++i) {
			if (v[j]>maior) {
				maior = v[j];
			}
		}
		v[i] = maior;
	}
	
	//impressao
	for (int i = 0; i < tam; i++)
		printf("%d ", v[i]);
	printf("\n");
	return 0;
}
