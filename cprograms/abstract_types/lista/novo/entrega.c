#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int cria_lista(t_lista *l){
	l->tamanho = 0;
	l->ini = NULL;
	return 1;
}

int lista_vazia(t_lista *l){
	return l->ini == NULL;
}

void destroi_lista(t_lista *l){
	t_nodo *p = l->ini, *q;

	if (p == NULL)
		return;

	while(p != NULL){
		q = p;
		p = p->prox;
		free(q);
	}

	l->tamanho = 0;
	l->ini = NULL;

	return;
}

int insere_inicio_lista(int x, t_lista *l){
	t_nodo *p = l->ini;

	l->ini = (t_nodo*) malloc(sizeof(t_nodo));
	if (l->ini == NULL)
		return 0;
	
	l->ini->chave = x;
	l->ini->prox = p;
	l->tamanho++;
	return 1;
}

int insere_fim_lista(int x, t_lista *l){
	t_nodo *p;
	p = l->ini;

	if (lista_vazia(l))
		return insere_inicio_lista(x, l);

	while(p->prox != NULL)	
		p = p->prox;

	p->prox = (t_nodo*) malloc(sizeof(t_nodo));
	p = p->prox;
	if (p == NULL)
		return 0;

	p->chave = x;
	p->prox = NULL;

	l->tamanho++;
	return 1; 
}

int insere_ordenado_lista(int x, t_lista *l){
	t_nodo *p = l->ini;
	t_nodo *old;

	if (lista_vazia(l))
		return insere_inicio_lista(x, l);

	while ((p->chave < x) && (p->prox != NULL)){
		old = p;
		p = p->prox;
	}

	if (p == l->ini && (p->chave > x))
		return insere_inicio_lista(x, l);

	if ((p->prox == NULL) && (p->chave < x))
		return insere_fim_lista(x, l);

	t_nodo *q;

	q = (t_nodo*) malloc(sizeof(t_nodo));
	old->prox = q;
	q->prox = p;
	q->chave = x;
	
	l->tamanho++;

	return 1; 
}

void imprime_lista(t_lista *l){
	t_nodo *p;
	p = l->ini;

	if (!lista_vazia(l)){
		while(p->prox != NULL){
			printf("%d ", p->chave);
			p = p->prox;
		}
		printf("%d \n", p->chave);
	}
	return;
}

int remove_primeiro_lista(int *item, t_lista *l){
	if (lista_vazia(l))
		return 0;

	
	t_nodo *p = l->ini;
	l->ini = l->ini->prox;
	*item = p->chave;
	l->tamanho--;
	free(p);
	return 1;
}

int remove_ultimo_lista(int *item, t_lista *l){
	if (lista_vazia(l))
		return 0;

	if (l->tamanho == 1)
		return remove_primeiro_lista(item, l);

	t_nodo *p = l->ini;
	t_nodo *old;

	while (p->prox != NULL){
		old = p;
		p = p->prox;
	}
	*item = p->chave;
	free(old->prox);
	old->prox = NULL;
	l->tamanho--;
	return 1;
}

int remove_item_lista(int chave, int *item, t_lista *l){
	if (lista_vazia(l))
		return 0;
	t_nodo *p = l->ini;
	t_nodo *old;
	
	if (p->chave == chave)
		return remove_primeiro_lista(item, l);	

	while (p->prox->prox != NULL && p->prox->chave != chave){
		old = p;
		p = p->prox;
	}

	if (p->prox->chave != chave)
		if (p->prox->prox == NULL)
			return 0;

	old = p;
	p = p->prox;

	*item = p->chave;
	t_nodo *aux = p;
	old->prox = p->prox;
	free(aux); 

	l->tamanho--;
	return 1;
}

int pertence_lista(int chave, t_lista *l){
	t_nodo *p = l->ini;

	while (p->prox != NULL && p->chave != chave)
		p = p->prox;

	if (p->chave == chave)
		return 1;
	if (p->prox == NULL)
		return 0;
	return 0;
}

int concatena_listas(t_lista *l, t_lista *m){
	t_nodo *p = m->ini;

	while(p != NULL){
		if (!insere_fim_lista(p->chave, l))
			return 0;
		p = p->prox;
	}

	l->tamanho += m->tamanho;
	return 1;
}

int copia_lista(t_lista *l, t_lista *m){
	t_nodo *p = l->ini;
	cria_lista(m);

	if (p == NULL)
		return 1;

	while(p->prox != NULL){
		if(!insere_fim_lista(p->chave, m))
			return 0;
		p = p->prox;
	}
	insere_fim_lista(p->chave, m);

	m->tamanho = l->tamanho;
	return 1;
}


int tamanho_lista(t_lista *l){
	return l->tamanho;
}

int* lista_para_vetor(t_lista *l){
	t_nodo *p = l->ini;
	int *v;
	if (lista_vazia(l))
		return NULL;

	v = (int*)malloc(l->tamanho * sizeof(int));
	if (v == NULL)
		return v;

	int i = 0;
	while(p != NULL){
		v[i] = p->chave;
		p = p->prox;
		i++;
	}

	return v;
}

int vetor_para_lista(t_lista *l, int *v, int tam){
	cria_lista(l);	
	int i;
	for (i = 0; i < tam; ++i){
		if(!insere_fim_lista(v[i], l))
			return 0;
	}

	return 1;
}