#ifndef __fila__
#define __fila__ 

struct t_nodo {
	int UT;
	int id;
	struct t_nodo *prox;
	struct t_nodo *prev;
};
typedef struct t_nodo t_nodo;

struct t_fila {
	t_nodo *ini;
	t_nodo *atual;
	t_nodo *fim;
	int tamanho;
};
typedef struct t_fila t_fila;

int inicializa_fila(t_fila *f);
int fila_vazia(t_fila *f);
int tamanho_fila(int *tam, t_fila *f);
int enfileira(int id, int item, t_fila *f);

int enfileira_prioridade(int id, int item, t_fila *f);

int desenfileira(int *id, int *item, t_fila *f);
int remove_fila(int *id, int *item, t_fila *f);
void imprime_fila(t_fila *f);
void destroi_fila(t_fila *f);

void incrementa_atual(t_fila *f);
int consulta_atual(int *id, int *item, t_fila *f);
int remove_atual(int *id, int *item, t_fila *f);
int inicializa_atual_fim(t_fila *f);
int inicializa_atual_inicio(t_fila *f);


#endif