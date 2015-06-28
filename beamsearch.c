#include <stdio.h>
#include <stdlib.h>
#include "permuta.h"

void removerUltimo(Lista* lista){
	Permuta* frente = NULL;
	Permuta* tras = NULL;

	while(frente != lista->ultimo){
		tras = frente;
		frente = frente->proximo;
	}

	lista->ultimo = tras;
	tras->proximo = NULL;

	liberarPermuta(frente);

	lista->tamanho--;
}

Permuta* beamSearch(Job** entrada, int n, int w){
	Lista* lista = inicializaLista(entrada, n);
	Permuta* item = NULL;
	Permuta* melhor = NULL;
	Permuta* filho = NULL;
	// int limiteUB = limite;
	int i;

	while(lista->primeiro != NULL){
		//retira o primeiro elemento da lista para gerar seus filhos
		item = lista->primeiro;
		lista->primeiro = lista->primeiro->proximo;
		lista->tamanho--;

		if(!eFolha(item)){
			if(item->lowerbound > lista->ultimo->){
				liberarPermuta(item);
			} else {
		 		//gera os filhos de item e (se for o caso) os insere na lista
				for(i=0; i < item->qtdeNaoPosicionados; i++){
					filho = criarFilho(item, n, i);
					if(lista->tamanho < w || filho->lowerbound < lista->ultimo->lowerbound){
					 	if(lista->tamanho > w){
					 		removerUltimo(lista);
					 	}
					 	lista = inserir(lista, filho);
					} else {
						liberarPermuta(filho);
					 	
					}
				}
				liberarPermuta(item);
			}
		} 
		// else {
		// 	if(item->lowerbound >= limiteUB){
		// 		liberarPermuta(item);
		// 	} else {
		// 		if(item->upperbound < limiteUB){
		// 			melhor = item;
		// 			limiteUB = item->upperbound;
		// 		}
		// 	}
		// }
	}

	return lista->primeiro;
}
