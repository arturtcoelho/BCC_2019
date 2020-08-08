#include <stdio.h>
#include "fila.h"

typedef struct aeroporto 
{
	t_fila att1, att2;
	t_fila att3, att4;
	t_fila dec1, dec2, dec3;

	int id_atual;
} t_aeroporto;

void inicializa_todas_filas(t_aeroporto *air);
void leitura_aterrissagens(t_aeroporto *air);
void leitura_decolagens(t_aeroporto *air);

void faz_decolagens(t_aeroporto *air);
void faz_aterrissagens(t_aeroporto *air);

void decrementa_tempos(t_aeroporto *air);


int main()
{
	t_aeroporto air;

	int tempo_simulacao;
	scanf("%d", &tempo_simulacao);

	inicializa_todas_filas(&air);
	
	int i;	
	for (i = 0; i < tempo_simulacao; ++i)
	{	
		printf("tempo de simulacao: %d\n", i);
	
		leitura_aterrissagens(&air);
		leitura_decolagens(&air);

		faz_decolagens(&air);
		faz_aterrissagens(air);



		decrementa_tempos(&air);
	}

	return 0;
}


void inicializa_todas_filas(t_aeroporto *air){
	inicializa_fila(&air->att1);
	inicializa_fila(&air->att2);
	inicializa_fila(&air->att3);
	inicializa_fila(&air->att4);

	inicializa_fila(&air->dec1);
	inicializa_fila(&air->dec2);
	inicializa_fila(&air->dec3);
	return;
}

void leitura_aterrissagens(t_aeroporto *air){
	return;
}

void leitura_decolagens(t_aeroporto *air){
	return;
}

void decrementa_tempos(t_aeroporto *air){

}

/*
pistas 1 2 3

filas 11, 12 e 21, 22

filas de decolagem 1 2 3

*/