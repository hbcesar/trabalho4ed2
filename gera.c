#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 200

void aleatorio(int n){
	int i;

	srand(time(NULL));

	for(i=0; i<n; i++){
		printf("%d %d %d\n", rand() % MAX, rand() % MAX, rand() % MAX);
	}
}

int main(int argc, char* argv []){
	int n, tipo;

	if(argc != 2){
		printf("Erro, número de argumentos inválidos!");
		exit(1);
	}
	//obtem o numero de elementos a serem gerados
	n = atoi(argv[1]);

	

	aleatorio(n);


	return 0;
}