#include <stdio.h>
#include <stdlib.h>
#include "permuta.h"

Permuta* branchAndBound(Job** entrada, int limite, int n){
	Lista* lista = inicializaLista(entrada, n);
	Permuta* item = NULL;
	Permuta* melhor = NULL;
	Permuta* filho = NULL;
	int limiteUB = limite;
	int i;

	while(lista->primeiro != NULL){
		//retira o primeiro elemento da lista para gerar seus filhos
		item = lista->primeiro;
		lista->primeiro = lista->primeiro->proximo;

		if(!eFolha(item)){
			if(item->lowerbound > limiteUB){
				liberarPermuta(item);
			} else {
		 		//gera os filhos de item e (se for o caso) os insere na lista
				for(i=0; i < item->qtdeNaoPosicionados; i++){
					filho = criarFilho(item, n, i);

					//caso tiverem um melhor caso pior do que o atual, são descartados
					if(filho->lowerbound > limiteUB){
					 	liberarPermuta(filho);
					} else {
					 	lista = inserir(lista, filho);
					}
				}
				liberarPermuta(item);
			}
		} else {
			//se forem nós folhas, são descartados ou é atualizado o melhor caso
			if(item->lowerbound > limiteUB){
				liberarPermuta(item);
			} else {
				if(item->upperbound <= limiteUB){
					melhor = item;
					limiteUB = item->upperbound;
				}
			}
		}
	}

	//é importante notar que pode acontecer que seja retornado NULO, 
	//neste caso significa que a entrada já era o melhor arranjo
	return melhor;
}