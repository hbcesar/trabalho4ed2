#include <stdio.h>
#include <stdlib.h>

struct listaPermutas{
	Permuta* item;
	struct listaPermutas* proximo;
}

typedef struct listaPermutas ListaPermutas;

ListaPermutas* iniciarLista(Permuta* p){
	ListaPermutas* nova = (ListaPermutas*) malloc(sizeof(ListaPermutas));

	nova->item = p;
	nova->proximo = NULL;
}

Permuta* inserir(Permuta* lista, Permuta* p){
	Permuta* frente, tras;

	if(lista == NULL){
		lista = p;
	} else {
		frente = lista;

		while((frente->lowerbound > p->lowerbound) && (frente != NULL)){
			tras = frente;
			frente = frente->proximo;
		}

		if(tras == NULL){
			p->proximo = lista;
		} else if (frente == NULL){
			tras->proximo = p;
		} else {
			tras->proximo = p;
			p->proximo = frente;
		}
	}
}