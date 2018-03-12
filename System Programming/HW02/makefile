all: hw02

hw02: main.o 
	gcc main.o -o listdir 

hw02.o: main.c
	gcc -c -ansi -pedantic-errors -Wall main.c

clean:
	rm *.o listdir
