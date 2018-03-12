
/***************************************************************
 *                                                             *
 *  HW-04                                                      *
 *  Student Name: Elif Seyma ARMAGAN                           *
 *  Student ID  : 151044042                                    *
 *  Date        : 23.10.2016                                   *
 *  Points      : A simple CPU simulation program with classes *
 *                                                             *
 ***************************************************************/

#include "requiredIncs.h" 

int main(int argc, char** argv){ 
	
	//command line parameters 
	const char* filename = argv[1]; 
	int option = atoi(argv[2]);
	
	//Testing class Memory
	Memory myMemory(option);
	myMemory.setMem(0, 100); 
	cout << myMemory.getMem(0) << endl;

	//Testing class CPU 
	CPU myCPU(option);
	myCPU.execute("MOV #0, R1", myMemory); 
	myCPU.execute("MOV R1, #1", myMemory);

	//Testing class CPUProgram 
	CPUProgram myCPUProgram(option); 
	myCPUProgram.ReadFile(filename); 
	cout << myCPUProgram.getLine(0) << endl; 
	cout << myCPUProgram.getLine(myCPUProgram.size() - 1) << endl;

	//Testing class Computer
	Computer myComputer1(myCPU, myCPUProgram, myMemory, option); 

	Computer myComputer2(option); 
	myComputer2.setCPU(myComputer1.getCPU());
	myComputer2.setCPUProgram(myComputer1.getCPUProgram()); 
	myComputer2.setMemory(myComputer1.getMemory()); 
	myComputer2.execute();
	
	return 0;
}