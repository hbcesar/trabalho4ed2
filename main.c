#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "permuta.h"
#include "bb.h"
#include "beamsearch.h"
#define W 3

//le entrada com atributos dos jobs
void lerEntrada(Job** entrada, int n){
	int i;
	int tempo, deadline, multa;

	for(i=0; i<n; i++){
		scanf("%d %d %d", &tempo, &deadline, &multa);
		entrada[i] = inicializarJob(i, tempo, deadline, multa);
	}
}

//libera o vetor de jobs
void liberarEntrada(Job** entrada, int n){
	int i;

	for(i=0; i < n; i++){
		free(entrada[i]);
	}

	free(entrada);
}

int main(int argc, char* argv []){
	Permuta* p = NULL;
	Permuta* k = NULL;
	Job** entrada = NULL;
	int n;

	n = atoi(argv[2]);

	entrada = (Job**) malloc(n * sizeof(Job*));

	if (n <= 0){
		printf("Numero invalido de elementos!\n");
		exit(1);
	}

	lerEntrada(entrada, n);
	imprimirEntrada(entrada, n);

	//de qualquer maneira, o beamsearch terá de ser realizado
	p = beamSearch(entrada, n, W);

	//se entrada de usuario estiver definindo bb, o faz
	if(strcmp(argv[1], "bb") == 0){
		k = branchAndBound(entrada, p->lowerbound, n);
	}
	
	// k pode ser nulo em dois casos:
	// 1 - BB não foi realizado
	// 2 - BB foi realizado mas a entrada já era o melhor caso
	if(k == NULL){
		imprimirResposta(p, n);
	} else {
		imprimirResposta(k, n);
		liberarPermuta(k);
	}

	liberarPermuta(p);
	liberarEntrada(entrada, n);

	return 0;
}