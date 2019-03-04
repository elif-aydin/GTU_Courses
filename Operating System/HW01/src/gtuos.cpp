#include <iomanip>
#include "8080emuCPP.h"
#include "gtuos.h"

using namespace std;

uint64_t GTUOS::handleCall(const CPU8080 & cpu)
{
    uint8_t registerA = cpu.state->a;

    uint64_t cycleCount = 0;

    if(registerA == (uint8_t) 1) //printB function
    {
        cycleCount = printB(cpu);
    }
    else if(registerA == (uint8_t) 2) //printMem function
    {
        cycleCount = printMem(cpu);
    }
    else if(registerA == (uint8_t) 3) //readB function
    {
        cycleCount = readB(cpu);
    }
    else if(registerA == (uint8_t) 4) //readMem function
    {
        cycleCount = readMem(cpu);
    }
    else if(registerA ==  5) //printStr function
    {
        cycleCount = printStr(cpu);
    }
    else if(registerA == (uint8_t) 6) //readStr function
    {
        cycleCount = readStr(cpu);
    }
    else if(registerA == (uint8_t) 7) //getRnd function
    {
        cycleCount = getRnd(cpu);
    }
    else
    {
        cout <<  "Unimplemented OS call";
        cout << "registerA :" << (int)registerA << endl;
        throw -1;
    }
    return cycleCount;
}

//Prints the contents of register B on the screen as a decimal number.
uint64_t GTUOS::printB(const CPU8080 &cpu)
{
    cout << "SYSTEM CALL : PRINT_B" << endl;
    printf("B: %d",cpu.state->b);
    cout << endl;
    return 10;
}

//Prints the contents of the memory pointed by registers B and C as a decimal number.
uint64_t GTUOS::printMem(const CPU8080 &cpu)
{
    uint16_t bc_address = (cpu.state->b << 8) | cpu.state->c;

    cout << "SYSTEM CALL : PRINT_MEM" << endl;
    cout << "BC: " << (int)cpu.memory->at(bc_address) << endl;
    return 10;
}

//Reads an integer from the keyboard and puts it in register B.
uint64_t GTUOS::readB(const CPU8080 &cpu)
{
    int input;
    scanf("%d",&input);
    cpu.state->b = input;
    return 10;
}

//Reads an integer from the keyboard and puts it in the memory location pointed by registers B and C
uint64_t GTUOS::readMem(const CPU8080 &cpu)
{
    int input;
    uint16_t bc_address = (cpu.state->b << 8) | cpu.state->c;

    cout << "SYSTEM CALL : READ_MEM" << endl;
    cin >> input;
    cpu.memory->at(bc_address) = input;
    return 10;
}

//Prints the null terminated string at the memory location pointed by B and C
uint64_t GTUOS::printStr(const CPU8080 &cpu)
{
    cout << "SYSTEM CALL : PRINT_STR" << endl;
    uint16_t bc_address = (cpu.state->b << 8) | cpu.state->c;
    while(cpu.memory->at(bc_address) != 0)
        cout << (char) cpu.memory->at(bc_address++);

    cout << endl;
    return 100;
}

//Reads the null terminated string from the keyboard and puts the
//result at the memory location pointed by B and C
uint64_t GTUOS::readStr(const CPU8080 &cpu)
{
    cout << "SYSTEM CALL : READ_STR" << endl;
    string input;
    cin >> input;
    uint16_t bc_address = (cpu.state->b << 8) | cpu.state->c;
    int i = 0;
    while (i < input.length())
        cpu.memory->at(bc_address++) = (uint8_t) input[i++];

    return 100;
}

//Produces a random byte and puts in register B
uint64_t GTUOS::getRnd(const CPU8080 &cpu)
{
    cout << "SYSTEM CALL : GET_RND" << endl;
    int pc = cpu.state->pc + 1;
    int sp = cpu.state->sp + 1;
    int b = cpu.state->b + 1;
    int c = cpu.state->c + 1;

    /*cout << "sp : " << sp << endl;
    cout << "sc : " << pc << endl;*/

    srand(static_cast<unsigned int>(time(NULL))); //i.e. non-associated value such as time (time(NULL) from ctime/time.h)
    int number = (int) (rand() * b * c * 17) % 3001;
    srand(static_cast<unsigned int>(time(NULL))); //i.e. non-associated value such as time (time(NULL) from ctime/time.h)
    int number2 = (int) (rand() * b * c * 13) % 1905;

    cpu.state->b = (number + number2) % 255;

    return 5;
}

int GTUOS::writeMemoryToFile(const CPU8080 &cpu, string fileName)
{
    ofstream memoryFile;
    memoryFile.open(fileName.c_str());

    if(!memoryFile.is_open())
    {
        cerr << "File could not open" << endl;
        return -1;
    }

    for(int i = 0x0000; i < 0x1000; i += 16)
    {
        memoryFile << hex << uppercase << setw(4) << i << " ";
        for(int j = 0x00; j < 0x10; ++j)
            memoryFile << "  " << hex << uppercase << setw(4) << (int)(cpu.memory->at(i+j));
        memoryFile << endl;
    }

    memoryFile.close();

    return 0;
}