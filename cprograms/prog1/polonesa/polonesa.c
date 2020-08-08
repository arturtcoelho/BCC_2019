#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "tad_pilha.h"
#define TAM 20

int leitura(char elemento[], char* operacao, double* numero) {
	scanf("%s", elemento);
	if ( isdigit(elemento[0]) ) {
		*numero = atof(elemento);
		return 0;
	}
	if (elemento[0] == '-')
		if (isdigit(elemento[1])){
			*numero = atof(elemento);
			return 0;
		}
	*operacao = elemento[0];
	return 1;
}

int main()
{
	tad_pilha p;
	char elemento[TAM];
	char operacao = '1';
	double numero;
	int tipo;
	inicializa_pilha(&p);

	while (operacao != 'q')
	{
		tipo = leitura(elemento, &operacao, &numero);
		if (tipo) 
		{ 
			if (tamanho_pilha(&p) >= 2)
			{ 
				double a, b;
				desempilha(&b, &p);
				desempilha(&a, &p);
				switch (operacao)
				{
					case '+': 
						empilha(a+b, &p);
						break;
					case '-':
						empilha(a-b, &p);
						break;
					case '*':
						empilha(a*b, &p);
						break;
					case '/':
						topo(&numero, &p);
						if (numero != 0)
							empilha(a/b, &p);
				}
			}
		} 
		else  
			empilha(numero, &p);
		
		topo(&numero, &p);
		printf("topo: %f\n", numero);
		
	} 

	topo(&numero, &p);
	printf("Resultado: %f\n", numero);

	return 0;
}