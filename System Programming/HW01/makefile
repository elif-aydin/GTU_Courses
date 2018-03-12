all: hw01

hw01: main.o 
	gcc main.o -o list 

hw01.o: main.c
	gcc -c -ansi -pedantic-errors -Wall main.c

clean:
	rm *.o list
