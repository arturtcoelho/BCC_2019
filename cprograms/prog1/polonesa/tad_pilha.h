#define MAX 100

typedef struct tad_pilha {
	int tam;
	double v[MAX];
} tad_pilha;

void inicializa_pilha (tad_pilha *p);
int pilha_vazia (tad_pilha *p);
int tamanho_pilha ( tad_pilha *p);
int empilha (double x,  tad_pilha *p);
int desempilha (double *t,  tad_pilha *p);
int topo (double *t,  tad_pilha *p);