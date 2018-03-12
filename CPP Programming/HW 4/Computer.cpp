#include "Computer.h"

Computer::Computer(CPU & cpu, CPUProgram & cpuProgram, Memory & memory, int opt)
{
    this->cpu = cpu;
    this->cpuProgram = cpuProgram;
    this->memory = memory;
    option = opt;
}

bool Computer::execute()
{
    while (!cpu.halted())
    {
        int pc = cpu.getPC();
        string inst = cpuProgram.getLine(pc-1);
        if (inst == "NULL")
        {
            cerr << "error" << endl;
            return false;
        }
        
        else
            cpu.execute(inst, memory);
    }
    return true;
}