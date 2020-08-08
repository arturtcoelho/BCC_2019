#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

typedef struct 
{
	int lin, col, geracao;
	int **matriz1;
	int **matriz2;
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
		print_tab(&tab);
		if (!exec_gen(&tab))
			break;
		sleep(1);
	}

	endwin();
	free(tab.matriz1);
	free(tab.matriz2);	
	return 0;
}

int inicializa_tab(tabuleiro_t *tab){
	int i;

	tab->matriz1 = malloc(tab->lin * sizeof(int*));
	tab->matriz2 = malloc(tab->lin * sizeof(int*));

	if (tab->matriz1 == NULL || tab->matriz2 == NULL)
		return 0;
	for (i = 0; i < tab->col; ++i)
	{
		*(tab->matriz1 + i) = malloc(tab->col * sizeof(int));
		*(tab->matriz2 + i) = malloc(tab->col * sizeof(int));
		if (*(tab->matriz1 +i) == NULL || *(tab->matriz2 +i) == NULL )
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
			scanf("%d", &tab->matriz1[i][j]);
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
	int i, j, volta;
	
	for (i = 0; i < tab->lin; ++i)
	{
		for (j = 0; j < tab->col; ++j)
		{
			volta = surround(tab, i, j);
			if (volta == 3){
				tab->matriz2[i][j] = 1;
			}
			if (volta > 3 || volta < 2){
				tab->matriz2[i][j] = 0;
			}
			if (volta == 2){
				tab->matriz2[i][j] = tab->matriz1[i][j];
			}
		}	
	}

	for (i = 0; i < tab->lin; ++i)
	{
		for (j = 0; j < tab->col; ++j)
		{
			tab->matriz1[i][j] = tab->matriz2[i][j];
		}
	}

	return 1;
}

int surround (tabuleiro_t* tab, int lin, int col){
	int i, j, cells = 0;
	for (i = lin-1; i <= lin+1; i++)
	{
		for (j = col-1; j <= col+1; j++)
		{
			if (i>=0 && j>=0 && i<tab->lin && j<tab->col)
			{
				if (tab->matriz1[i][j])
					cells++;
			}
		}
	}
	if (tab->matriz1[lin][col])
		cells--;
	return cells;
}

void print_tab(tabuleiro_t* tab){
	int i, j;
	clear();
	move(0, 0);
	for (i = 0; i < tab->lin; ++i)
	{
		for (j = 0; j < tab->col; ++j)
		{
			if (tab->matriz1[i][j] == 1){
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