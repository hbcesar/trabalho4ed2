all: COMPILAR
	./trab4 bb 13 < entrada13.txt

COMPILAR:
	gcc -c bb.c
	gcc -c permutas.c
	gcc -c main.c
	#gcc -c beamsearch.c
	gcc bb.o permutas.o main.o -o trab4