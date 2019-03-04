#ifndef H_GTUOS
#define H_GTUOS

#include "8080emuCPP.h"
#include <ctime>       /* time */
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <fcntl.h>

#define MAX_THREAD 20
#define MAX_FILES 4096
#define NUM_OF_BLOCKS 4096
#define BLOCK_SIZE 256

using namespace std;

typedef enum
{
    READY = 0,
    BLOCKED = 1,
    RUNNING = 2
} ThreadState;

typedef struct
{
    uint16_t id;
    State8080 state8080;    // saved registers like a,b,c,sp,pc
    uint64_t startTime;    // starting time of process, the cycle number of the CPU
    uint64_t usedCycle;        // how many cycle the process had used so far
    ThreadState  state;    // ready, blocked, running
    uint64_t address;      //physical addres of the memory location of process
    uint8_t isAlive;
    uint16_t waitId;
} TableEntry;

typedef struct
{
    int id;
    int startingBlock;
    uint64_t size;  // # blocks
    uint64_t bytes;
    int pos;
    int posBlock;
    char name[256];
    uint64_t createTime;
    uint64_t lastModifiedTime;
    uint64_t lastAccessTime;
    bool isOpen;
} FileEntry;

typedef struct
{
    char data[BLOCK_SIZE];
    int active;
} Block;

typedef struct
{
    FileEntry* fileTable;
    Block* blocks;
    int nextEmptyBlock;
    int nextFileEntry;
} FileSystem;

class GTUOS
{

public:
    GTUOS() {}
    GTUOS(CPU8080 &cpu, int debugType, char * fs);
    uint64_t run(CPU8080 &cpu);
    uint16_t handleCall(const CPU8080 & cpu, uint64_t totalCycles);
    uint64_t printB(const CPU8080 &cpu);
    uint64_t printMem(const CPU8080 &cpu);
    uint64_t readB(const CPU8080 &cpu);
    uint64_t fileCreate(const CPU8080 &cpu, uint64_t totalCycles);
    uint64_t fileOpen(const CPU8080 &cpu, uint64_t totalCycles);
    uint64_t fileClose(const CPU8080 &cpu, uint64_t totalCycles);
    uint64_t fileRead(const CPU8080 &cpu, uint64_t totalCycles);
    uint64_t fileWrite(const CPU8080 &cpu, uint64_t totalCycles);
    uint64_t fileSeek(const CPU8080 &cpu, uint64_t totalCycles);
    uint64_t dirRead(const CPU8080 &cpu, uint64_t totalCycles);
    uint64_t readMem(const CPU8080 &cpu);
    uint64_t printStr(const CPU8080 &cpu);
    uint64_t readStr(const CPU8080 &cpu);
    uint64_t getRnd(const CPU8080 &cpu);
    uint64_t tCreate(const CPU8080 &cpu, uint64_t totalCycles);
    uint64_t tExit(const CPU8080 &cpu);
    uint64_t tJoin(const CPU8080 &cpu);
    uint64_t tYield(const CPU8080 &cpu);
    int writeMemoryToFile(const CPU8080 &cpu, std::string fileName);
    string getFileTableInfo();


private:
    State8080 state8080;
    TableEntry* threadTable;
//    FileEntry* fileTable;
//    Block* blocks;

    FileSystem * fileSystem;
    char * fileSystemName;
    uint16_t currentThread;
    void switchThread(uint16_t p1, uint16_t p2, CPU8080 &cpu); // p1 -> p2
    uint16_t getNextThread() const; //round-robin
    FileEntry * searchFile(const char * name) const;
    int remainingSpaceInFile(FileEntry * file) const;

    int debugType;
    bool yieldCalled;

};

#endif
