#include <stdio.h>

int main()
{
	int v[100], tam, x;

	//leitura
	scanf("%d", &tam);
	for (int i = 0; i < tam; i++)
		scanf("%d", &v[i]);
	
	//insertion sort
	for (int i = 1; i < tam; i++) {
		x = v[i];
		for (int j = i; j >= 0; j--) {
			if (x <= v[j-1])
				v[j] = v[j-1];
			else 
				v[j-1] = x;
		}
	}

	
	//impressao
	for (int i = 0; i < tam; i++)
		printf("%d ", v[i]);
	printf("\n");
	return 0;
}