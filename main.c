#include <stdio.h>
#include <stdlib.h>
#include "permuta.h"
#include "bb.h"
#include "beamsearch.h"

void lerEntrada(Job** entrada, int n){
	int i;
	int tempo, deadline, multa;

	for(i=0; i<n; i++){
		scanf("%d %d %d", &tempo, &deadline, &multa);
		entrada[i] = inicializarJob(i, tempo, deadline, multa);
	}
}

Permuta* teste(Job** entrada, int n){
	int i;
	Permuta* teste = inicializaPermuta(n);

	for(i=0; i < n; i++){
		teste->posicionados[i] = entrada[i];
		teste->qtdePosicionados++;
		teste->upperbound += entrada[i]->multa;
		teste->tempoDecorrido += entrada[i]->tproc;

		if(entrada[i]->deadline < teste->tempoDecorrido)
			teste->lowerbound += entrada[i]->multa;
	}

	return teste;
}

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

	p = teste(entrada, n);
	
	k = branchAndBound(entrada, p->lowerbound, n);
	//k = beamSearch(entrada, n, 2);

	if(k == NULL){
		printf("K ta nulo viu?\n");
		imprimirResposta(p, n);
	} else {
		imprimirResposta(k, n);
	}

	liberarEntrada(entrada, n);

	return 0;
}