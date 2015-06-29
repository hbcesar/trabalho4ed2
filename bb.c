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

	while(!eFolha(lista->primeiro)){
		//retira o primeiro elemento da lista para gerar seus filhos
		item = lista->primeiro;
		lista->primeiro = lista->primeiro->proximo;
		lista->tamanho--;

		//atualiza o limite atual
		if(item->upperbound <= limiteUB){
			limiteUB = item->upperbound;
		}

		//gera os filhos de item e (se for o caso) os insere na lista
		for(i=0; i < item->qtdeNaoPosicionados; i++){
			filho = criarFilho(item, n, i);

			//se o filho criado tiver um pior caso melhor do que o limite atual
			//ou essa listinha marota tiver vazia,
			//insere o pobre coitado
			if((filho->upperbound <= limiteUB) || (lista->tamanho == 0)){
				lista = inserir(lista, filho);
			} else{
				liberarPermuta(filho);
			}
		}

		//libera esse menino do qual foram gerados filhos
		liberarPermuta(item);
	}

	melhor = lista->primeiro;

	lista->primeiro = lista->primeiro->proximo;
	
	liberarLista(lista);

	return melhor;
}