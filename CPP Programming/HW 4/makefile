all: hw4

hw4: main.o CPU.o CPUProgram.o Memory.o Computer.o
	g++ main.o CPU.o CPUProgram.o Memory.o Computer.o -o exe

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

CPU.o: CPU.cpp
	g++ -c -std=c++11 CPU.cpp

CPUProgram.o: CPUProgram.cpp
	g++ -c -std=c++11 CPUProgram.cpp

Memory.o: Memory.cpp
	g++ -c -std=c++11 Memory.cpp

Computer.o: Computer.cpp
	g++ -c -std=c++11 Computer.cpp

clean: 
	rm *.o exe
