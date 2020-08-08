#include <stdlib.h>
#include <stdio.h>
#include "lib_lista.h"
#include "lib_lista_complementar.h"

int inicializa_lista(t_lista *l){
	l->tamanho = 0;
	l->ini = (t_nodo*) malloc(sizeof(t_nodo));
	l->fim = (t_nodo*) malloc(sizeof(t_nodo));
	l->atual = NULL;

	if (l->ini == NULL || l->fim == NULL)
		return 0;

	l->ini->prox = l->fim;
	l->ini->prev = NULL;
	l->fim->prox = NULL;
	l->fim->prev = l->ini;

	return 1;
}

int lista_vazia(t_lista *l){
	return !l->tamanho;
}

void destroi_lista(t_lista *l){
	if(!lista_vazia(l)){
		inicializa_atual_inicio(l);
		int a;
		while(remove_item_atual(&a, l));
	}

	free(l->ini);
	free(l->fim);
	l->tamanho = 0;
	return;
}

int insere_inicio_lista(int item, t_lista *l){
	l->atual = (t_nodo*) malloc(sizeof(t_nodo));

	if (l->atual == NULL)
		return 0;

	l->atual->chave = item;
	l->atual->prev = l->ini;
	l->atual->prox = l->ini->prox;

	l->ini->prox->prev = l->atual;
	l->ini->prox = l->atual;

	l->tamanho++;
	l->atual = NULL;
	return 1;
}

int tamanho_lista(int *tam, t_lista *l){
	return l->tamanho;
}

int insere_fim_lista(int item, t_lista *l){
	l->atual = (t_nodo*) malloc(sizeof(t_nodo));

	if (l->atual == NULL)
		return 0;

	l->atual->chave = item;
	l->atual->prox = l->fim;
	l->atual->prev = l->fim->prev;

	l->fim->prev->prox = l->atual;
	l->fim->prev = l->atual;

	l->tamanho++;
	l->atual = NULL;
	return 1;
}

int insere_ordenado_lista(int item, t_lista *l){
	if (lista_vazia(l))
		return insere_inicio_lista(item, l);

	l->fim->chave = item+1;
	inicializa_atual_inicio(l);

	while(l->atual->chave < item){
		incrementa_atual(l);
	}

	if (l->atual == l->fim)
		return insere_fim_lista(item, l);

	t_nodo *novo = (t_nodo*) malloc(sizeof(t_nodo));
	if (novo == NULL)
		return 0;

	novo->chave = item;
	novo->prox = l->atual;
	novo->prev = l->atual->prev;

	l->atual->prev->prox = novo;
	l->atual->prev = novo;  

	l->tamanho++;
	return 1;
}

int remove_inicio_lista(int *item, t_lista *l){
	if (lista_vazia(l))
		return 0; 
	inicializa_atual_inicio(l);
	return remove_item_atual(item, l);  
}

int remove_fim_lista(int *item, t_lista *l){
	if (lista_vazia(l))
		return 0; 
	inicializa_atual_fim(l);
	return remove_item_atual(item, l);
}

int remove_item_lista(int chave, int *item, t_lista *l){
	if (lista_vazia(l))
		return 0;
	l->fim->chave = chave;
	inicializa_atual_inicio(l);
	while((l->atual != l->fim) && (l->atual->chave != chave))
		incrementa_atual(l);

	if (l->atual == l->fim)
		return 0;
	return remove_item_atual(item, l);
}

int pertence_lista(int chave, t_lista *l){
	if (lista_vazia(l))
		return 0;
	l->fim->chave = chave;
	inicializa_atual_inicio(l);
	while((l->atual != l->fim) && (l->atual->chave != chave))
		incrementa_atual(l);

	if (l->atual == l->fim)
		return 0;
	return 1;
}

int inicializa_atual_inicio(t_lista *l){
	if (l->ini->prox == l->fim)
		return 0;
	l->atual = l->ini->prox;
	return 1;
}

int inicializa_atual_fim(t_lista *l){
	if (l->fim->prev == l->ini)
		return 0;
	l->atual = l->fim->prev;
	return 1;
}

void incrementa_atual(t_lista *l){
	l->atual = l->atual->prox;
	return;
}

void decrementa_atual(t_lista *l){
	l->atual = l->atual->prev;
	return;
}

int consulta_item_atual(int *item, t_lista *l){
	if (l->atual == l->fim)
		return 0;
	*item = l->atual->chave;
	return 1;
}

int remove_item_atual(int *item, t_lista *l){
	if (l->atual == l->fim)
		return 0;
	*item = l->atual->chave;

	t_nodo *p = l->atual;

	l->atual->prev->prox = l->atual->prox;
	l->atual->prox->prev = l->atual->prev;

	l->atual = l->atual->prox;

	l->tamanho--;
	free(p);
	return 1;
}