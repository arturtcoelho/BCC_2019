#define MAX 100

typedef struct tad_pilha {
	int tam;
	char v[MAX];
} tad_pilha;

void inicializa_pilha (tad_pilha *p);
int pilha_vazia (tad_pilha *p);
int tamanho_pilha ( tad_pilha *p);
int empilha (char x,  tad_pilha *p);
int desempilha (char *t,  tad_pilha *p);
int topo (char *t,  tad_pilha *p);