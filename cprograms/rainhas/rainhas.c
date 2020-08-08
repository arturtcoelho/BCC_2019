#include <stdio.h>

typedef struct{
	int board[8][8];
	int num_rainhas;
} tab_t;

void inicializa(tab_t *tab){
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			tab->board[i][j] = 0;
		}
	}
	tab->num_rainhas = 0;
}

void imprime(tab_t *tab){
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			printf("%d ", tab->board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int linha_vazia(tab_t* tab, int i)
{
    int j;
    for (j = 0; j < 8; j++){
        if (tab->board[i][j] != 0){
        	// printf("linha\n");
            return 0;
        }
    }
    return 1;
}

int esta_na_matriz(int i, int j)
{
    if (0 <= i && i < 8 && 0 <= j && j < 8)
        return 1;
    return 0;
}

int diagonais_vazias(tab_t* tab, int linha, int coluna)
{
    /*cima-esquerda*/
    int i = linha;
    int j = coluna;
    while( esta_na_matriz(i, j) )
    {
        if (tab->board[i][j] != 0){
        	// printf("diagonal\n");
            return 0;
        }

        i--;
        j--;
    }
        
    /* cima-direita*/
    i = linha;
    j = coluna;    
    while( esta_na_matriz(i, j) )
    {
        if (tab->board[i][j] != 0){
        	// printf("diagonal\n");
            return 0;         
        }
        i--;
        j++;
    }

    /*baixo-esquerda*/
    i = linha;
    j = coluna;    
    while( esta_na_matriz(i, j) )
    {
        if (tab->board[i][j] != 0){
        	// printf("diagonal\n");
            return 0;         
        }
        i++;
        j--;
    }

    /*baixo-direita*/
    i = linha;
    j = coluna;    
    while( esta_na_matriz(i, j) )
    {
        if (tab->board[i][j] != 0){
        	// printf("diagonal\n");
            return 0;         
        }
        i++;
        j++;
    }

    return 1;
}

int coluna_vazia(tab_t* tab, int j)
{
    int i;
    for(i = 0; i < 8; i++){
		if (tab->board[i][j] != 0){
			// printf("coluna\n");
			return 0;
		}
    }
    return 1;
}

int podecolocar(tab_t* tab, int i, int j)
{
    if ( linha_vazia(tab, i) && coluna_vazia(tab, j) && diagonais_vazias(tab, i, j) && tab->board[i][j] == 0)
        return 1;
    return 0;
}

int resolve(tab_t *tab, int lin, int col){
	if (tab->num_rainhas == 8){
		return 1;
	}

	int i = lin, j = col;
	for (; i < 8; ++i)
	{
		for (; j < 8; ++j)
		{
			if (podecolocar(tab, i, j))
			{
				tab->board[i][j] = 1;
				tab->num_rainhas++;
				if (resolve(tab, 0, 0))
				{
					return 1;
				} 
				else 
				{
					tab->board[i][j] = 0;
					tab->num_rainhas--;
				}
			}
		}
		j = 0;
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	tab_t tab;
	inicializa(&tab);
    resolve(&tab, 0, 0);
    imprime(&tab);
	return 0;
}