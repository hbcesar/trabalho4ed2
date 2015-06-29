#include <stdio.h>
#include <stdlib.h>
#include "permuta.h"

Permuta* beamSearch(Job** entrada, int n, int w){
	Lista* lista = inicializaLista(entrada, n);
	Permuta* item = NULL;
	Permuta* melhor = NULL;
	Permuta* filho = NULL;
	int i;

	//nesse caso, assume que quando a primeira folha for gerada, ela estará no número minimo de W menores LB da heuristica
	while(!eFolha(lista->primeiro)){
		//retira o primeiro elemento da lista para gerar seus filhos
		item = lista->primeiro;
		lista->primeiro = lista->primeiro->proximo;
		lista->tamanho--;
		
		for(i=0; i < item->qtdeNaoPosicionados; i++){

			filho = criarFilho(item, n, i);

			//se a lista ainda precisar atingir o tamanho 
			//ou se esse menino que vier a ser inserido for melhor que o pior que tiver na lista (the last one),
			//entao insere
			if(lista->tamanho < w || filho->lowerbound < lista->ultimo->lowerbound){
				lista = inserir(lista, filho);

				if(lista->tamanho > w){
					removerUltimo(lista);
				}

			} else {
				liberarPermuta(filho);
			}
		}

	}

	melhor = lista->primeiro;

	lista->primeiro = lista->primeiro->proximo;
	liberarLista(lista);

	return melhor;
}
