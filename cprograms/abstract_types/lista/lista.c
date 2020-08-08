#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int cria_lista(list_t *l){
	l->size = 0;
	l->beg = NULL;
	return 1;
}

int lista_vazia(list_t *l){
	return !l->size;
}

void destroi_lista(list_t *l){
	node_t *p = l->beg, *q;

	if (p == NULL)
		return;

	while(p->next != NULL){
		q = p;
		p = p->next;
		free(q);
	}

	l->size = 0;
	l->beg = NULL;

	return;
}

int insere_inicio_lista(element_t x, list_t *l){
	node_t *p = l->beg;

	l->beg = (node_t*) malloc(sizeof(node_t));
	if (l->beg == NULL)
		return 0;
	
	l->beg->key = x;
	l->beg->next = p;
	l->size++;
	return 1;
}

int insere_fim_lista(element_t x, list_t *l){
	node_t *p;
	p = l->beg;

	if (lista_vazia(l))
		return insere_inicio_lista(x, l);

	while(p->next != NULL)	
		p = p->next;

	p->next = (node_t*) malloc(sizeof(node_t));
	p = p->next;
	if (p == NULL)
		return 0;

	p->key = x;
	p->next = NULL;

	l->size++;
	return 1; 
}

int insere_ordenado_lista(element_t x, list_t *l){
	node_t *p = l->beg;
	node_t *old;

	if (lista_vazia(l))
		return insere_inicio_lista(x, l);

	while ((p->key < x) && (p->next != NULL)){
		old = p;
		p = p->next;
	}

	if (p == l->beg && (p->key > x))
		return insere_inicio_lista(x, l);

	if ((p->next == NULL) && (p->key < x))
		return insere_fim_lista(x, l);

	node_t *q;

	q = (node_t*) malloc(sizeof(node_t));
	old->next = q;
	q->next = p;
	q->key = x;
	
	l->size++;

	return 1; 
}

void imprime_lista(list_t *l){
	node_t *p;
	p = l->beg;

	if (!lista_vazia(l)){
		while(p->next != NULL){
			printf("%d ", p->key);
			p = p->next;
		}
		printf("%d \n", p->key);
	}
	return;
}

int remove_primeiro_lista(element_t *item, list_t *l){
	if (lista_vazia(l))
		return 0;
	*item = l->beg->key;
	
	node_t *p = l->beg;
	l->beg = l->beg->next;
	l->size--;
	free(p);
	return 1;
}

int remove_ultimo_lista(element_t *item, list_t *l){
	if (lista_vazia(l))
		return 0;
	node_t *p = l->beg;
	node_t *old;

	while (p->next != NULL){
		old = p;
		p = p->next;
	}
	*item = p->key;
	free(old->next);
	old->next = NULL;
	l->size--;
	return 1;
}

int remove_item_lista(element_t chave, element_t *item, list_t *l){
	if (lista_vazia(l))
		return 0;
	node_t *p = l->beg;
	node_t *old;
	
	if (p->key == chave)
		return remove_primeiro_lista(item, l);	

	while (p->next->next != NULL && p->next->key != chave){
		old = p;
		p = p->next;
	}

	if (p->next->key != chave)
		if (p->next->next == NULL)
			return 0;

	old = p;
	p = p->next;

	*item = p->key;
	node_t *aux = p;
	old->next = p->next;
	free(aux); 

	l->size--;
	return 1;
}

int pertence_lista(element_t chave, list_t *l){
	node_t *p = l->beg;

	while (p->next != NULL && p->key != chave)
		p = p->next;

	if (p->key == chave)
		return 1;
	if (p->next == NULL)
		return 0;
}

int concatena_listas(list_t *l, list_t *m){
	node_t *p = l->beg;

	while(p->next != NULL)
		p = p->next;

	p->next = m->beg;
	l->size += m->size;
	return 1;
}

int copia_lista(list_t *l, list_t *m){
	node_t *p = l->beg;
	cria_lista(m);

	if (p == NULL)
		return 1;

	while(p->next != NULL){
		if(!insere_fim_lista(p->key, m))
			return 0;
		p = p->next;
	}
	insere_fim_lista(p->key, m);

	m->size = l->size;
	return 1;
}


int tamanho_lista(list_t *l){
	return l->size;
}

element_t* lista_para_vetor(list_t *l){
	node_t *p = l->beg;
	element_t *v;
	if (lista_vazia(l))
		return NULL;

	v = (element_t*)malloc(l->size * sizeof(element_t));
	if (v == NULL)
		return v;

	int i = 0;
	while(p != NULL){
		v[i] = p->key;
		p = p->next;
		i++;
	}

	return v;
}

int vetor_para_lista(list_t *l, element_t *v, int tam){
	cria_lista(l);	
	int i;
	for (i = 0; i < tam; ++i){
		if(!insere_fim_lista(v[i], l))
			return 0;
	}

	return 1;
}