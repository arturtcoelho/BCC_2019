#include <stdlib.h>
#include <stdio.h>
#include "tad_pilha.h"

int complementar (char a, char b){
	if (a == '(') {
		if (b == ')')
			return 1;
		return 0;
	}
	if (a == '{') {
		if (b == '}')
			return 1;
		return 0;
	}
	if (a == '[') {
		if (b == ']')
			return 1;
		return 0;
	}
	return 0;
}


int main()
{
	tad_pilha p;
	char c = '1', aux;	
	inicializa_pilha(&p);
	while (c != '0') {
	scanf("%c", &c);
		if (c == '(' || c == '{' || c == '[') {
			empilha(c, &p);
		}
		else {
			topo(&aux, &p);
			if (complementar(aux, c)) {
				desempilha(&aux, &p);
			}
			else {
				break;
			}
		}
	}	

	if (pilha_vazia(&p))
		printf("SIM\n");
	else
		printf("NAO\n");
	return 0;
}