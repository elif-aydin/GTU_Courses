#include "Computer.h"

Computer::Computer(CPU & cpu, CPUProgramDyn & cpuProgramDyn, Memory & memory, int opt)
{
    this->cpu = cpu;
    this->cpuProgramDyn = cpuProgramDyn;
    this->memory = memory;
    option = opt;
}

bool Computer::execute()
{
    while (!cpu.halted()) // Halted olmadigi surece
    {
        int pc = cpu.getPC();
        string inst = cpuProgramDyn.getLine(pc-1);
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