all: hw03

hw03: main.o withPipeandFIFO.o
	gcc main.o withPipeandFIFO.o -o withPipeandFIFO 

hw03.o: main.c
	gcc -c -ansi -pedantic-errors -Wall main.c

withPipeandFIFO.o: withPipeandFIFO.c
	gcc -c -ansi -pedantic-errors -Wall withPipeandFIFO.c

clean: 
	rm *.o withPipeandFIFO
	clear
