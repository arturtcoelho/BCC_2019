#include <stdio.h>
#include "lista.h"

int main(int argc, char const *argv[])
{
	t_lista l, m, n;
	int i;
	cria_lista(&l);
	cria_lista(&m);
	cria_lista(&n);

	for (i = 0; i < 10; ++i){
		insere_inicio_lista(i, &l);
		insere_ordenado_lista(i,&m);
		insere_fim_lista(i,&n);
	}
	imprime_lista(&l);
	imprime_lista(&m);
	imprime_lista(&n);

	concatena_listas(&l,&m);

	int item;
	for (i = 0; i < 10; ++i){
		remove_primeiro_lista(&item, &l);
		remove_primeiro_lista(&item, &m);
		remove_primeiro_lista(&item, &n);
	}

	printf("%d\n", lista_vazia(&l));	
	printf("%d\n", lista_vazia(&m));	
	printf("%d\n", lista_vazia(&n));	

	printf("%d\n", l.tamanho);
	imprime_lista(&l);

	while(!lista_vazia(&l)){
		remove_primeiro_lista(&item, &l);
		printf("i\n");
	}

	printf("%d\n", lista_vazia(&l));	
	printf("%d\n", lista_vazia(&m));	
	printf("%d\n", lista_vazia(&n));	
	return 0;
}