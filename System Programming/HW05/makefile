all: hw05

hw05: main.o 
	gcc main.o -lpthread -g -o grepSh 

hw05.o: main.c
	gcc -c -pedantic-errors -g -lpthread -Wall main.c

clean:
	rm *.o grepSh
