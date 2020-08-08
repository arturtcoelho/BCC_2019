#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "tad_pilha.h"
#include <unistd.h>

typedef struct 
{
	int lin, col, geracao;
	int **matriz;
	tad_pilha morre;
	tad_pilha nasce;
} tabuleiro_t;

int inicializa_tab(tabuleiro_t* tab);
void ler_matriz(tabuleiro_t* tab);
void inicializa_ncurses();
int exec_gen(tabuleiro_t* tab);
int surround (tabuleiro_t* tab, int lin, int col);
void print_tab(tabuleiro_t* tab);

int main(int argc, char const *argv[])
{
	tabuleiro_t tab;
	int i;

	if (argc == 3){
		tab.lin = atoi(argv[1]);
		tab.col = atoi(argv[2]);
	}
	else{
		printf("insira o numero certo de argumentos\n");
		exit(1);
	}

	if (!inicializa_tab(&tab)){
		printf("erro de alocacao\n");
		exit(1);
	}
	printf("insira a matriz\n");
	ler_matriz(&tab);
	printf("insira o numero de geracoes\n");
	scanf("%d", &tab.geracao);

	inicializa_ncurses();	
	for (i = 0; i < tab.geracao; ++i)
	{
		if (!exec_gen(&tab))
			break;
		print_tab(&tab);
		sleep(1);
	}

	endwin();
	free(tab.matriz);
	return 0;
}

int inicializa_tab(tabuleiro_t *tab){
	int i;

	tab->matriz = malloc(tab->lin * sizeof(int*));
	if (tab->matriz == NULL)
		return 0;
	for (i = 0; i < tab->col; ++i)
	{
		*(tab->matriz + i) = malloc(tab->col * sizeof(int));
		if (*(tab->matriz +i) == NULL)
			return 0;
	}
	return 1;
}

void ler_matriz(tabuleiro_t* tab){
	int i, j;
	for (i = 0; i < tab->lin; ++i)
	{
		for (j = 0; j < tab->col; ++j)
		{
			scanf("%d", &tab->matriz[i][j]);
		}
	}
}


void inicializa_ncurses (){
	initscr();
	raw();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	noecho();
	curs_set(FALSE);
	cbreak();

	start_color();
	return;
}

int exec_gen(tabuleiro_t* tab){
	int volta, i, j;
	coordenada_t c;
	for (i = 0; i < tab->lin; ++i)
	{
		for (j = 0; j < tab->col; ++j)
		{
			volta = surround(tab, i, j);
			c.lin = i;
			c.col = j;
			if ((volta > 3 || volta < 2) && tab->matriz[i][j]){
				empilha(c, &tab->morre);
			}
			if (volta == 3){
				empilha(c, &tab->nasce);
			}
		}
	}
	if (pilha_vazia(&tab->morre) && pilha_vazia(&tab->nasce))
		return 0;
	while (!pilha_vazia(&tab->morre)){
		c = desempilha(&tab->morre);
		tab->matriz[c.lin][c.col] = 0;
	}
	while (!pilha_vazia(&tab->nasce)){
		c = desempilha(&tab->nasce);
		tab->matriz[c.lin][c.col] = 1;
	}
	return 1;
}

int surround (tabuleiro_t* tab, int lin, int col){
	int i, j, cells = 0;
	for (i = lin-1; i < lin+1; ++i)
	{
		for (j = col-1; j < col+1; ++j)
		{
			if ((i >= 0) && (i <= tab->lin) && (j >= 0) && (j <= tab->col)){
				if (tab->matriz[i][j])
					cells++;
			}
		}
	}
	return cells+1;
}

void print_tab(tabuleiro_t* tab){
	int i, j;
	clear();
	move(0, 0);
	for (i = 0; i < tab->lin; ++i)
	{
		for (j = 0; j < tab->col; ++j)
		{
			if (tab->matriz[i][j] == 1){
				addch('0');
				addch(' ');
			}
			else{
				addch('.');
				addch(' ');
			}
		}
		addch('\n');
	}
	refresh();
}