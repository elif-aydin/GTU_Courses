#include <iomanip>
#include "8080emuCPP.h"
#include "gtuos.h"

using namespace std;

//Baslatilan program ilk thread olarak kabul edilir
GTUOS::GTUOS(CPU8080 &cpu, int debugType)
{
    this->debugType = debugType;
    threadTable = (TableEntry *) calloc(sizeof(TableEntry), MAX_THREAD); // calloc for initialize
    threadTable[0].state8080 = (*cpu.state);
    threadTable[0].state8080.cc = (*cpu.state).cc;
    threadTable[0].id = 0;
    threadTable[0].state = RUNNING;
    threadTable[0].isAlive = 1;
    threadTable[0].startTime = 0;
    threadTable[0].usedCycle = 0;
    threadTable[0].address = cpu.state->pc;
    currentThread = 0;
    yieldCalled = false;
}

uint64_t GTUOS::run(CPU8080 &cpu)
{
    uint64_t totalCycles = 0;
    int cycle = 0;
    unsigned int temp = 0;
    bool end = false;
    int syscallCount = 0;

    while (!end)
    {
        //if (debugType == 2)


        if (syscallCount > 0)
            -- syscallCount;


        temp = cpu.Emulate8080p(this->debugType);
        if (cpu.isSystemCall())
        {
            syscallCount = 6; //System call procedure ending inst count
            temp = handleCall(cpu, totalCycles);
        }

        threadTable[currentThread].usedCycle += temp;
        cycle += temp;
        totalCycles += temp;

        if (syscallCount == 0 && (yieldCalled || (cycle / 100) > 0 || threadTable[currentThread].state == BLOCKED) && !cpu.isHalted())  // round robin cycle
        {
            cycle = 0;
            uint16_t nextIndex = getNextThread();
            if (nextIndex != currentThread) // no need if same thread gets from getNextThread
                switchThread(currentThread, nextIndex, cpu);
            yieldCalled = false;
            continue;
        }

        if(cpu.isHalted())
        {
            end = true;
            continue;
        }
    }

    return totalCycles;
}

void GTUOS::switchThread(uint16_t t1, uint16_t t2, CPU8080 &cpu)
{
    if (debugType == 2)
    {
        cout << "Thread switch from ID " << t1 << " to ID " <<  t2 << endl;
        cout << "Used cycles of ID " << t1 << ": " << threadTable[t1].usedCycle << endl;
    }
    else if (debugType == 3)
    {
        cout << setw(5) << "ID"  << setw(7) << "STime" << setw(7) << "Used" << setw(7) << "Addr" << setw(15) << "BlockedFor" << setw(10) << "State" << endl;
        for (int i = 0; i < MAX_THREAD; ++i)
        {
            if (threadTable[i].isAlive == 1)
            {
                cout << setw(5) << threadTable[i].id ;
                cout << setw(7) << threadTable[i].startTime ;
                cout << setw(7) << threadTable[i].usedCycle;
                cout << setw(7) << threadTable[i].address ;
                cout << setw(15) << threadTable[i].waitId ;
                switch ((int)threadTable[i].state)
                {
                    case 0: cout << setw(10) << "Ready";
                        break;
                    case 1: cout << setw(10) << "Blocked";
                        break;
                    case 2: cout << setw(10) << "Running";
                    default:
                        break;
                }
                cout << endl;
            }
        }
    }

    threadTable[t1].state8080 = (*cpu.state);
    if (threadTable[t1].state != BLOCKED)   // running ise
        threadTable[t1].state = READY;

    (*cpu.state) = threadTable[t2].state8080;
    threadTable[t2].state = RUNNING;
    currentThread = t2;
}


uint16_t GTUOS::getNextThread() const
{
    // look forward
    for (uint8_t i = currentThread + 1; i < MAX_THREAD; ++i)
        if (threadTable[i].isAlive && threadTable[i].state == READY)
            return i;

    // look backward
    for (uint8_t i = 0; i < currentThread; ++i)
        if (threadTable[i].isAlive && threadTable[i].state == READY)
            return i;

    return currentThread;
}


uint16_t GTUOS::handleCall(const CPU8080 & cpu, uint64_t totalCycles)
{
    //std::cin.get();
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
    else if(registerA == (uint8_t) 8) // TExit function
    {
        cycleCount = tExit(cpu);
    }
    else if(registerA == (uint8_t) 9) //  TJoin function
    {
        cycleCount = tJoin(cpu);
    }
    else if(registerA == (uint8_t) 10) // TYield function
    {
        cycleCount = tYield(cpu);
    }
    else if(registerA == (uint8_t) 11) // TCreate function
    {
        cycleCount = tCreate(cpu, totalCycles);
    }
    else
    {
        cout <<  "Unimplemented OS call";
        cout << "registerA :" << (int)registerA << endl;
        throw -1;
    }
    return cycleCount;
}

uint64_t  GTUOS::tExit(const CPU8080 &cpu)
{
    cout << "SYSTEM CALL : TExit" << endl;
    threadTable[currentThread].isAlive = 0;
    for (uint16_t i = 0; i < MAX_THREAD; ++i)
    {
        if (i != currentThread && threadTable[i].state == BLOCKED && threadTable[i].waitId == currentThread)
            threadTable[i].state = READY;
    }
    return 50;
}

uint64_t  GTUOS::tYield(const CPU8080 &cpu)
{
    cout << "SYSTEM CALL : TYield" << endl;
    yieldCalled = true;
    //currentThread = getNextThread();
    return 40;
}

uint64_t  GTUOS::tJoin(const CPU8080 &cpu)
{
    cout << "SYSTEM CALL : TJoin" << endl;
    threadTable[currentThread].state = BLOCKED;
    threadTable[currentThread].waitId = cpu.state->b;
    return 40;
}

//It works like the pthread_create call of UNIX
uint64_t GTUOS::tCreate(const CPU8080 &cpu, uint64_t totalCycles)
{
    cout << "SYSTEM CALL : TCreate" << endl;
    uint16_t bc_address = (cpu.state->b << 8) | cpu.state->c;
    uint8_t nextEmpty = -1; // pick empty position to create thread
    for (uint8_t i = 0; i < MAX_THREAD; ++i)
    {
        if (i != currentThread && !threadTable[i].isAlive)
        {
            nextEmpty = i;
            break;
        }
    }
    if (nextEmpty == -1) // if memory full then fail and return 0
    {
        cpu.state->b = 0;
        return 0;
    }

    threadTable[nextEmpty].state8080 = (*cpu.state);
    threadTable[nextEmpty].state8080.cc = (*cpu.state).cc;
    threadTable[nextEmpty].id = nextEmpty;
    threadTable[nextEmpty].state = READY;
    threadTable[nextEmpty].isAlive = 1;
    threadTable[nextEmpty].address = bc_address;
    threadTable[nextEmpty].state8080.pc = bc_address;
    threadTable[nextEmpty].startTime = totalCycles;
    threadTable[nextEmpty].usedCycle = 0;
    threadTable[nextEmpty].state8080.pc = bc_address;

    cpu.state->b = nextEmpty; // It returns the thread ID in register B on success

    return 80;
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