#include "8080emuCPP.h"
#include "gtuos.h"
#include "memory.h"


int main (int argc, char**argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: prog exeFile debugOption\n";
        exit(1);
    }

//argv[2] = "1";
//argv[1] = "part5.com";
//argv[1] = "printstr.com";

    int DEBUG = atoi(argv[2]);

    memory mem;
    CPU8080 theCPU(&mem);
    GTUOS	theOS;
    uint64_t cycles = 0;

    theCPU.ReadFileIntoMemoryAt(argv[1], 0x0000);
    do
    {
        cycles += theCPU.Emulate8080p(DEBUG);
        if(theCPU.isSystemCall())
            cycles += theOS.handleCall(theCPU);
        if(DEBUG == 2)
            std::cin.get(); //wait for enter
    }	while (!theCPU.isHalted());

    std::cout << "Total cycles: " << cycles << std::endl;

    std::string fileName = argv[1];
    std::string delim = ".";
    std::string token = fileName.substr(0, fileName.find(delim));
    std::string memoryFile = token + ".mem";

    theOS.writeMemoryToFile(theCPU, memoryFile);

    return 0;
}
