/*implementacao do tipo pilha*/
#define MAX 100

typedef struct tad_pilha {
	int tam;
	char v[MAX];
} tad_pilha;

/*zera o tamanho da pilha*/
void inicializa_pilha (tad_pilha *p) {
	(*p).tam = -1;
}

/*1 se pilha vazia, 0 se houver elemento*/
int pilha_vazia (tad_pilha *p) {
	if ((*p).tam == -1) return 1;
	return 0;
}

/*retorna o tamanho*/
int tamanho_pilha ( tad_pilha *p) {
	return (*p).tam + 1;
}

/*empilha o elemento, devolve 1, caso nao haja espaco, devolve 0 e nao empilha*/
int empilha (char x,  tad_pilha *p) {
	if ((*p).tam == MAX-1) return 0;
	(*p).tam++;
	(*p).v[(*p).tam] = x;
	return 1;
}

/*desempilha se ouver, em t, devolve 1, caso nao, devolve 0*/
int desempilha (char *t,  tad_pilha *p) {
	if ((*p).tam == -1) return 0;
	*t = (*p).v[(*p).tam];
	(*p).tam--;
	return 1;
}

/*retorna o elemento no topo em t, retorna 1, caso nao, retorna 0*/
int topo (char *t,  tad_pilha *p) {
	if ((*p).tam == -1) return 0;
	*t = (*p).v[(*p).tam];
	return 1;
}