all: hw04

hw04: main.o 
	gcc main.o -lpthread -g -o grepTh 

hw02.o: main.c
	gcc -c -pedantic-errors -g -lpthread -Wall main.c

clean:
	rm *.o grepTh log.txt
