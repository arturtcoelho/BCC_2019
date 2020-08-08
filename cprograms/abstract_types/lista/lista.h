typedef element_t int;

struct t_nodo {
    element_t key;
    struct t_nodo *next;
};
typedef struct t_nodo t_nodo;

typedef struct list_t {
    t_nodo *beg;
    int size;
} list_t;

int cria_lista(list_t *l);
int lista_vazia(list_t *l);
void destroi_lista(list_t *l);
int insere_inicio_lista(element_t x, list_t *l);
int insere_fim_lista(element_t x, list_t *l);
int insere_ordenado_lista(element_t x, list_t *l);
void imprime_lista(list_t *l);
int remove_primeiro_lista(element_t *item, list_t *l);
int remove_ultimo_lista(element_t *item, list_t *l);
int remove_item_lista(element_t chave, element_t *item, list_t *l);
int pertence_lista(element_t chave, list_t *l);
int concatena_listas(list_t *l, list_t *m);
int copia_lista(list_t *l, list_t *m);