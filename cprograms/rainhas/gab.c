#include <stdio.h>
int linha_vazia(char m[8][8], int i)
{
    int j;
    for (j = 0; j < 8; j++)
        if (m[i][j] != '0')
            return 0;
    
    return 1;
}

int esta_na_matriz(int i, int j)
{
    if (0 <= i && i < 8 && 0 <= j && j < 8)
        return 1;
    else
        return 0;
    
}

int diagonais_vazias(char m[8][8], int linha, int coluna)
{
    /cima-esquerda/
    int i = linha;
    int j = coluna;
    while( esta_na_matriz(i, j) )
    {
        if (m[i][j] != '0')
            return 0;

        i--;
        j--;
    }
        
    /* cima-direita*/
    i = linha;
    j = coluna;    
    while( esta_na_matriz(i, j) )
    {
        if (m[i][j] != '0')
            return 0;         
        i--;
        j++;
    }

    /baixo-esquerda/
    i = linha;
    j = coluna;    
    while( esta_na_matriz(i, j) )
    {
        if (m[i][j] != '0')
            return 0;         
        i++;
        j--;
    }

    /baixo-direita/
    i = linha;
    j = coluna;    
    while( esta_na_matriz(i, j) )
    {
        if (m[i][j] != '0')
            return 0;         
        i++;
        j++;
    }

    return 1;
}

int coluna_vazia(char m[8][8], int j)
{
    int i;
    for(i = 0; i < 8; i++)
    if (m[i][j] != '0')
            return 0;
    
    return 1;
}

int pode_colocar(char m[8][8], int i, int j)
{
    if ( linha_vazia(m, i) && coluna_vazia(m, j) && diagonais_vazias(m, i, j) && m[i][j] == '0' )
        return 1;
    else
        return 0;
    
}

void zera_matriz(char m[8][8])
{
    int i, j;
    for (i = 0; i < 8; i++)
        for(j = 0; j < 8; j++)
            m[i][j] = '0';
}

void imprime_matriz(char m[8][8])
{
    int i, j;
    for (i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if (m[i][j] == '0')
                printf("- ");
            else
                printf("%c ", m[i][j]);
        }
        printf("\n");
    }
}

int coloca_rainha(char m[8][8], int i_anterior, int j_anterior, int rainhas_posicionadas)
{
    if ( rainhas_posicionadas == 8 )
        return 1;

    int i, j;
    for(i = i_anterior; i < 8; i++)
        for(j = 0; j < 8; j++)
        {
            if ( pode_colocar(m, i, j) )
            {
                rainhas_posicionadas = rainhas_posicionadas + 1;
                m[i][j] = '@';
                if( coloca_rainha(m, i, j, rainhas_posicionadas) )
                    return 1;
                else
                {
                    rainhas_posicionadas = rainhas_posicionadas - 1;
                    m[i][j] = '0'; 
                }    
            }
        }
    
    return 0;
     
}

int main()
{
    char m[8][8];
    zera_matriz(m);

    int rainhas_posicionadas = 0;
    coloca_rainha(m, 0, 0, rainhas_posicionadas);

    imprime_matriz(m);

    return 1;
}