#ifndef COMPUTER_H
#define COMPUTER_H

#include "CPU.h"
#include "CPUProgramDyn.h"
#include "Memory.h"

using namespace std;
using namespace HW6;

class Computer 
{
public:
    Computer(){}
    Computer(int opt) { option = opt; }    
    Computer(CPU & cpu, CPUProgramDyn & program, Memory & myMemory, int opt); 
    bool execute();
    
    /* Getters and Setters */ 
    inline CPU getCPU() const { return cpu; }
    inline CPUProgramDyn getCPUProgramDyn() const { return cpuProgramDyn; }
    inline Memory getMemory() const { return memory; }
    inline void setCPU(CPU cpu) { this->cpu = cpu; this->cpu.setPC(1); }
    inline void setCPUProgramDyn (CPUProgramDyn cpuProgramDyn) { this->cpuProgramDyn = cpuProgramDyn; }
    inline void setMemory(Memory memory) { this->memory = memory; this->memory.initMemory(); }
     
private:
    CPU cpu;
    CPUProgramDyn cpuProgramDyn;
    Memory memory;
    int option;
};

#endif /* COMPUTER_H */