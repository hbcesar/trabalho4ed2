#include <stdio.h>
#include <stdlib.h>
#include "permuta.h"

//aloca estrutura interface pra lista de permutas
Lista* alocaLista(){
	Lista* novo = (Lista*)malloc(sizeof(Lista));

	novo->primeiro = NULL;
	novo->ultimo = NULL;
	novo->tamanho = 0;

	return novo;
}

//seta as configuracoes da interface lista, de modo que esta fiquei pronta para
//ser processada por um dos dois algoritmos, ou seja,
//aloca a lista e já gera a raiz da "arvore" de permutacoes
Lista* inicializaLista(Job** entrada, int n){
	Lista* lista = alocaLista();
	lista->primeiro = gerarRaiz(entrada, n);
	lista->ultimo = lista->primeiro;
	lista->tamanho = 1;

	return lista;
}

//aloca espaco na memoria para uma nova permuta
Permuta* inicializaPermuta(int n){
	Permuta* novo = (Permuta*)malloc(sizeof(Permuta));

	novo->a_pos = (Job**)malloc(n*sizeof(Job*));
	novo->posicionados = (Job**)malloc(n*sizeof(Job*));
	novo->lowerbound = 0;
	novo->upperbound = 0;
	novo->tempoDecorrido = 0;
	novo->qtdePosicionados = 0;
	novo->qtdeNaoPosicionados = 0;
	novo->proximo = NULL;

	return novo;
}

//aloca espaco na memoria para um job
Job* inicializarJob(int id, int tproc, int deadline, int multa){
	Job* novo = (Job*)malloc(sizeof(Job));

	novo->id = id;
	novo->tproc = tproc;
	novo->deadline = deadline;
	novo->multa = multa;

	return novo;
}

//gera o primeiro nó da arvore de permutacoes,
//ou seja, uma permuta sem nenhum job já ordenado
Permuta* gerarRaiz(Job** entrada, int n){
	int i;
	Permuta* primeira = inicializaPermuta(n);
	primeira->qtdeNaoPosicionados = n;

	for(i=0; i < n; i++){
		primeira->a_pos[i] = entrada[i];
		primeira->upperbound += entrada[i]->multa;
	}

	return primeira;
}

//adiciona um job ao vetor de jobs ordenados da permuta
//e seta as configuracoes de tempo, lb e ub.
void adicionarPosicionado(Permuta* p, Job* job){
	p->posicionados[p->qtdePosicionados++]= job;

	p->tempoDecorrido += job->tproc;

	if(p->tempoDecorrido > job->deadline){
		p->lowerbound += job->multa;
		p->upperbound += job->multa;
	}
}

//adiciona um job ao vetor de jobs não ordenados da permuta
//e seta as configuracoes de tempo, lb e ub.
void adicionarNaoPosicionados(Permuta* p, Job* job){
	p->a_pos[p->qtdeNaoPosicionados++] = job;
	p->upperbound += job->multa;

	if(p->tempoDecorrido + job->tproc > job->deadline)
		p->lowerbound += job->multa;
}

//faz copia de uma estrutura de permutacoes
void copiarPermuta(Permuta* origem, Permuta* destino, int k){
	int i;

	for(i = 0; i < origem->qtdePosicionados; i++){
		adicionarPosicionado(destino, origem->posicionados[i]);
	}

	//copia o vetor de não posicionados, pulando o infeliz que vai ser posicionado
	//e atualizando os LB e UP.
	for(i=0; i < origem->qtdeNaoPosicionados; i++){
		if(i != k)
			adicionarNaoPosicionados(destino, origem->a_pos[i]);
	}
}

//recebe a permuta de origem (p), o numero de jobs(n) e o índice do
//job que sairá do vetor de não posicionados e irá para o lindo vetor de posicionados
Permuta* criarFilho(Permuta* p, int n, int k){
	int i;
	Permuta* nova = inicializaPermuta(n);

	//copia a permuta, sem adicionar novo menino a ser posicionado
	copiarPermuta(p, nova, k);

	//copia o menino que vai ser posicionado pro lugarzinho dele
	adicionarPosicionado(nova, p->a_pos[k]);

	return nova;
}

//insere lista de permutas ordenada pelo upper bound
Lista* inserir(Lista* lista, Permuta* p){
	Permuta* frente = NULL;
	Permuta* tras = NULL;

	if(lista->primeiro == NULL){
		lista->primeiro = p;
		lista->ultimo = p;
	} else {
		frente = lista->primeiro;

		while((frente != NULL) && (frente->lowerbound < p->lowerbound)){
			tras = frente;
			frente = frente->proximo;
		}

		if(tras == NULL){
			p->proximo = lista->primeiro;
			lista->primeiro = p;
		} else if (frente == NULL){
			tras->proximo = p;
			lista->ultimo = p;
		} else {
			tras->proximo = p;
			p->proximo = frente;
		}
	}

	lista->tamanho++;
	return lista;
}

//remove o ultimo elemento da lista
//essa funcao só é usada pelo BS
void removerUltimo(Lista* lista){
	Permuta* frente = lista->primeiro;
	Permuta* tras = NULL;

	while(frente->proximo != NULL){
		tras = frente;
		frente = frente->proximo;
	}

	lista->ultimo = tras;
	tras->proximo = NULL;

	liberarPermuta(frente);

	lista->tamanho--;
}

int eFolha(Permuta* p){
	if(p->qtdeNaoPosicionados == 0){
		return 1;
	} else {
		return 0;
	}
}

void imprimirEntrada(Job** entrada, int n){
	int i;

	for(i=0; i < n; i++){
		printf("%d %d %d\n", entrada[i]->tproc, entrada[i]->deadline, entrada[i]->multa);
	}
}

void imprimirResposta(Permuta* p, int n){
	int i;

	printf("%d:", p->lowerbound);

	for(i=0; i < p->qtdePosicionados; i++){
		printf(" %d", p->posicionados[i]->id);
	}

	printf("\n");
}

void liberarPermuta(Permuta* p){
	if(p!=NULL){
		free(p->a_pos);
		free(p->posicionados);
		free(p);
	}
}

