#include "cpu.h"
using namespace std;



int main(int argc, char** argv) 
{
    if(argc != 3)
    {
        cerr << "You have to enter 3 parameters" << endl;
        return 1;
    }
    
    //file daki toplam satir sayisini bulmak icin fonksiyonu cagirir.
    int numberOfLines = findNumberOfLines(argv[1]);
    if (numberOfLines > MAX_SIZE)
    {
        cerr << "Number of lines max: " << MAX_SIZE << endl;
        return 1;
    }
    
    int option = 0;
    if (convertToNumber(option, argv[2]) == false)
    {
        cerr << "You have to write option as an int!" << endl;
        return -1;
    }
    
    if (!(option == 0 || option == 1 || option == 2)) 
    {
        cerr << "There are only three options: 0, 1 and 2." << endl;
        return -1;
    }

    int regArr[6] = {0}; // en fazla 5 reg olabilir. Uygulamak kolay olsun diye 0 ignore edilir. 1. eleman r1 olur.
    string lines[MAX_SIZE];
    int memory[50] = {0}; // Memory can hold only 50 integers. So it ends with 49

    readFile(argv[1], lines, numberOfLines);
    
    bool result = executeCommands(option, lines, numberOfLines, regArr, numberOfLines, memory);
    
    if (result == true)
    {
        cout <<"Program finished succesfully"<<endl;
        return 0;
    }

    else
    {   
        cerr << "Program finished with an error"<<endl;
        return 1;
    }
}