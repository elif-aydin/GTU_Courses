#ifndef H_GTUOS
#define H_GTUOS

#include "8080emuCPP.h"
#include <ctime>       /* time */
#include <iostream>
#include <fstream>

class GTUOS
{
public:

    uint64_t handleCall(const CPU8080 & cpu);
    uint64_t printB(const CPU8080 &cpu);
    uint64_t printMem(const CPU8080 &cpu);
    uint64_t readB(const CPU8080 &cpu);
    uint64_t readMem(const CPU8080 &cpu);
    uint64_t printStr(const CPU8080 &cpu);
    uint64_t readStr(const CPU8080 &cpu);
    uint64_t getRnd(const CPU8080 &cpu);
    int writeMemoryToFile(const CPU8080 &cpu, std::string fileName);
};

#endif
