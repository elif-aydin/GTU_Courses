/***************************************************************
 *                                                             *
 *  HW-03                                                      *
 *  Student Name: Elif Seyma ARMAGAN                           *
 *  Student ID  : 151044042                                    *
 *  Date        : 23.10.2016                                   *
 *  Points      : A simple CPU simulation program with classes *
 *                                                             *
 ***************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include "CPU.h" // includes cpu header
#include "CPUProgram.h" // includes cpuProgram header

using namespace std;

int main(int argc, char** argv) 
{
    CPUProgram myProg(argv[1]); //file name
    CPU myCPU(argv[2]); // option
    
    while (!myCPU.halted())
    {
        string instruction = myProg.getLine(myCPU.getPC()); //get instruction
        myCPU.execute(instruction); //execute instruction
    }
    return 0;
}