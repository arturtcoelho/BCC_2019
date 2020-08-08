#include <stdio.h>
#include <stdlib.h> 

int main()
{
	int *v, tam, x;
	scanf("%d", &tam);
	v = malloc(tam* sizeof(int));
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
	/*for (int i = 0; i < tam; i++)
		printf("%d ", v[i]);
	printf("\n");
	*/
	int i = 0;
	while(i < tam-1 && v[i] > v[i+1])
	{		
		i++;
	}
	if (i == tam)
		printf("seu merda %d %d\n", v[i], v[i+1]);
	else
		printf("uhul\n");
	free(v);
	return 0;
}
