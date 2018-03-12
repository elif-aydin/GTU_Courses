all:hw6

hw6: _mainTester.o CPU.o CPUProgramDyn.o Memory.o Computer.o
	g++ _mainTester.o CPU.o CPUProgramDyn.o Memory.o Computer.o -o exe

_mainTester.o: _mainTester.cpp
	g++ -c -std=c++11 _mainTester.cpp

CPU.o: CPU.cpp
	g++ -c -std=c++11 CPU.cpp

CPUProgramDyn.o: CPUProgramDyn.cpp
	g++ -c -std=c++11 CPUProgramDyn.cpp

Memory.o: Memory.cpp
	g++ -c -std=c++11 Memory.cpp

Computer.o: Computer.cpp
	g++ -c -std=c++11 Computer.cpp

clean: 
	rm *.o exe
