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
	unsigned int flag = 0;

	while(lista->primeiro != NULL){
		//retira o primeiro elemento da lista para gerar seus filhos
		item = lista->primeiro;
		lista->primeiro = lista->primeiro->proximo;

		//verifica se o melhor caso deve ser atualizado
		if(item->upperbound <= limiteUB){
			//liberarPermuta(melhor);
			melhor = item;
			limiteUB = item->upperbound;
			flag = 1;
		} else if (item->lowerbound > limiteUB){
			liberarPermuta(item);
			continue;
		}

		//gera os filhos de item e (se for o caso) os insere na lista
		for(i=0; i < item->qtdeNaoPosicionados; i++){
			filho = criarFilho(item, n, i);

			if(filho->lowerbound > limiteUB){
				//caso tiverem um melhor caso pior do que o atual, são descartados
				liberarPermuta(filho);
			} else {
				//senao, verifica se ele é muito legal
				if(filho->upperbound <= limiteUB){
					//liberarPermuta(melhor);
					melhor = filho;
					limiteUB = filho->upperbound;
					flag = 1;
				}

				//e os insere na lista
				lista = inserir(lista, filho);
			}
		}

		if(!flag){
			//se o item atual nao tiver sido setado como o melhor, entao ele pode ser apagado
			liberarPermuta(item);
			flag = 0;
		}

	}

	free(lista);

	//é importante notar que pode acontecer que seja retornado NULO, 
	//neste caso significa que a entrada já era o melhor arranjo
	return melhor;
}