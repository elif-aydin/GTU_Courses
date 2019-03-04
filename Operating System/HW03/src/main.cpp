#include "8080emuCPP.h"
#include "gtuos.h"
#include "memory.h"

using namespace std;
int main (int argc, char**argv)
{
	if (argc != 4)
	{
        std::cerr << "Usage: prog exeFile fileSystem.dat debugOption\n";
        exit(1);
    }

    int debug = atoi(argv[3]);
    char * fs = argv[2];
    char * name = argv[1];

    memory mem;
    CPU8080 theCPU(&mem);
    theCPU.ReadFileIntoMemoryAt(name, 0x0000);
    GTUOS	theOS(theCPU, debug, fs);
    uint64_t cycles = theOS.run(theCPU);

    std::cout << "Total cycles: " << cycles << std::endl;

    if (debug == 0 || debug == 1) {
        std::string fileName = name;
        std::string delim = ".";
        std::string token = fileName.substr(0, fileName.find(delim));
        std::string memoryFile = token + ".mem";

        theOS.writeMemoryToFile(theCPU, memoryFile);

        string s = theOS.getFileTableInfo();
        cout << "Directory Info:" << endl;
        cout << s << endl;
    }
    

    return 0;
}
