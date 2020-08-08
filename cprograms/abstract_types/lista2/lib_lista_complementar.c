#include "lib_lista_complementar.h"

void imprime_lista(t_lista *l){
	if (lista_vazia(l))
		return;

	inicializa_atual_inicio(l);
	for (int n;consulta_item_atual(&n, l); incrementa_atual(l))
		printf("%d ", n);
	printf("\n");
}

int copia_lista(t_lista *l, t_lista *c){
	if (lista_vazia(l))
		return 1;

	destroi_lista(c);
	inicializa_lista(c);

	int a;
	inicializa_atual_inicio(l);
	while(consulta_item_atual(&a, l)){
		incrementa_atual(l);
		if (!insere_fim_lista(a, c))
			return 0;
	}
	return 1;
}

int concatena_listas(t_lista *l, t_lista *c){ 
	if (lista_vazia(c))
		return 1;

	int a;
	inicializa_atual_inicio(c);
	while(consulta_item_atual(&a, c)){
		incrementa_atual(c);
		if (!insere_fim_lista(a, l))
			return 0;
	}
	return 1;
}

int ordena_lista(t_lista *l){
	t_lista aux;
	inicializa_lista(&aux);
	copia_lista(l, &aux);

	destroi_lista(l);
	inicializa_lista(l);

	int n;
	inicializa_atual_inicio(&aux);
	while(consulta_item_atual(&n, &aux)){
		if (!insere_ordenado_lista(n, l))
			return 0;
		incrementa_atual(&aux);
	}
	destroi_lista(&aux);
	return 1;
}

int intercala_listas(t_lista *l, t_lista *m, t_lista *i){
	destroi_lista(i);
	inicializa_lista(i);

	int n;
	inicializa_atual_inicio(l);
	inicializa_atual_inicio(m);
	while(consulta_item_atual(&n, l)){
		if(!insere_ordenado_lista(n, i))
			return 0;
		incrementa_atual(l);
	}
	while(consulta_item_atual(&n, m)){
		if(!insere_ordenado_lista(n, i))
			return 0;
		incrementa_atual(m);
	}
	return 1;
}