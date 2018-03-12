all: hw3

hw3: main.o CPU.o CPUProgram.o
	g++ main.o CPU.o CPUProgram.o -o exe

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

CPU.o: CPU.cpp
	g++ -c -std=c++11 CPU.cpp

CPUProgram.o: CPUProgram.cpp
	g++ -c -std=c++11 CPUProgram.cpp

clean: 
	rm *.o exe