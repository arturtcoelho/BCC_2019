#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

int inicializa_fila(t_fila *f){
	f->tamanho = 0;
	f->ini = (t_nodo*) malloc(sizeof(t_nodo));
	f->fim = (t_nodo*) malloc(sizeof(t_nodo));
	f->atual = NULL;

	if (f->ini == NULL || f->fim == NULL)
		return 0;

	f->ini->prox = f->fim;
	f->ini->prev = NULL;
	f->fim->prox = NULL;
	f->fim->prev = f->ini;

	return 1;
}

int fila_vazia(t_fila *f){
	return !f->tamanho;
}

int tamanho_fila(int *tam, t_fila *f){
	return f->tamanho;
}

int enfileira(int id, int UT, t_fila *f){
	f->atual = (t_nodo*) malloc(sizeof(t_nodo));

	if (f->atual == NULL)
		return 0;

	f->atual->id = id;
	f->atual->UT = UT;
	f->atual->prev = f->ini;
	f->atual->prox = f->ini->prox;

	f->ini->prox->prev = f->atual;
	f->ini->prox = f->atual;

	f->tamanho++;
	f->atual = NULL;
	return 1;
}

int enfileira_prioridade(int id,int UT, t_lista *l){
	l->atual = (t_nodo*) malloc(sizeof(t_nodo));

	if (l->atual == NULL)
		return 0;

	l->atual->id = id;
	l->atual->UT = UT;
	l->atual->prox = l->fim;
	l->atual->prev = l->fim->prev;

	l->fim->prev->prox = l->atual;
	l->fim->prev = l->atual;

	l->tamanho++;
	l->atual = NULL;
	return 1;
}

int desenfileira(int *id, int *UT, t_fila *f){
	if (fila_vazia(f))
		return 0; 
	inicializa_atual_fim(f);
	return remove_atual(id, UT, f);
}

int remove_fila(int *id, int *UT, t_fila *f){
	if (fila_vazia(f))
		return 0;
	f->fim->UT = *UT;
	inicializa_atual_inicio(f);
	while((f->atual != f->fim) && (f->atual->UT != *UT))
		incrementa_atual(f);

	if (f->atual == f->fim)
		return 0;
	return remove_atual(id, UT, f);
}

void imprime_fila(t_fila *f){
	if (fila_vazia(f))
		return;

	int id;
	inicializa_atual_inicio(f);
	for (int n; consulta_atual(&id, &n, f); incrementa_atual(f))
		printf("%d ", n);
	printf("\n");
}

void destroi_fila(t_fila *f){
	if(!fila_vazia(f)){
		inicializa_atual_inicio(f);
		int a, b;
		while(remove_atual(&a, &b, f));
	}

	free(f->ini);
	free(f->fim);
	f->tamanho = 0;
	return;
}

int inicializa_atual_inicio(t_fila *f){
	if (f->ini->prox == f->fim)
		return 0;
	f->atual = f->ini->prox;
	return 1;
}

int inicializa_atual_fim(t_fila *f){
	if (f->fim->prev == f->ini)
		return 0;
	f->atual = f->fim->prev;
	return 1;
}

int remove_atual(int *id, int *UT, t_fila *f){
	if (f->atual == f->fim)
		return 0;
	*UT = f->atual->UT;
	*id = f->atual->id;

	t_nodo *p = f->atual;

	f->atual->prev->prox = f->atual->prox;
	f->atual->prox->prev = f->atual->prev;

	f->atual = f->atual->prox;

	f->tamanho--;
	free(p);
	return 1;
}

int consulta_atual(int *id, int *UT, t_fila *f){
	if (f->atual == f->fim)
		return 0;
	*UT = f->atual->UT;
	return 1;
}

void incrementa_atual(t_fila *f){
	f->atual = f->atual->prox;
	return;
}
