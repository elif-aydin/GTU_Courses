all: server clients

server: server.o 
	gcc server.o -lm -lpthread -g -o server

server.o: server.c
	gcc -c -g -lpthread -pedantic-errors -Wall server.c

clients: clients.o 
	gcc clients.o -lm -lpthread -g -o clients

clients.o: clients.c
	gcc -c -g -lpthread -pedantic-errors -Wall clients.c

clean:
	rm *.o clients server *.log
