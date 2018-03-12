all: seeWhat timerServer showResult
	mkdir log

seeWhat: seeWhat.o
	gcc  seeWhat.o -o seeWhat

seeWhat.o: seeWhat.c
	gcc -c -g  -pedantic-errors -Wall seeWhat.c

timerServer: timerServer.o
	gcc  timerServer.o -o timerServer

timerServer.o: timerServer.c
	gcc -c -g  -pedantic-errors -Wall timerServer.c

showResult: showResult.o
	gcc  showResult.o -o showResult

showResult.o: showResult.c
	gcc -c -g  -pedantic-errors -Wall showResult.c

clean:
	rm *.o *.log seeWhat timerServer showResult ctrlFIFO resFIFO -rf log
	clear