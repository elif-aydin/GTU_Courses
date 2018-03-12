#ifndef COMPUTER_H
#define COMPUTER_H

#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"

using namespace std;

class Computer 
{
public:
    Computer(){}
    Computer(int opt) { option = opt; }    
    Computer(CPU & cpu, CPUProgram & program, Memory & myMemory, int opt); 
    bool execute();
    
    /* Getters and Setters */ 
    inline CPU getCPU() const { return cpu; }
    inline CPUProgram getCPUProgram() const { return cpuProgram; }
    inline Memory getMemory() const { return memory; }
    inline void setCPU(CPU & cpu) { this->cpu = cpu; this->cpu.setPC(1); }
    inline void setCPUProgram(CPUProgram & cpuProgram) { this->cpuProgram = cpuProgram; }
    inline void setMemory(Memory & memory) { this->memory = memory; this->memory.initMemory(); }
     
private:
    CPU cpu;
    CPUProgram cpuProgram;
    Memory memory;
    int option;
};

#endif /* COMPUTER_H */