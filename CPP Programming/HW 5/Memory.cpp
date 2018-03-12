#include "Memory.h"
using namespace std;

Memory::Memory() 
{
    initMemory();
}

Memory::Memory(int opt) 
{
    if (!(opt == 0 || opt == 1 || opt == 2))
    {
        cerr << "Options can be only 0 and 1 " << endl;
        cerr << "Default is assigning to 0." << endl;
        opt = 0;    
    }
    
    this-> option = opt;
    initMemory();
}

void Memory::initMemory()
{
    for(int i = 0; i < 50; i++) //initialize all memory elements to zero.
        setMem(i, 0);
}

bool Memory::getMem(const string num, int &number)
{
    int memoryAddress;
    if(getTheAddress(memoryAddress, num))
    {
        number = memory[memoryAddress];
        return true;
    }
    else 
    {
        cerr << "String is not a number" << endl;
        return false;
    }
}

bool Memory::convertToNumber(int &total, const string & element)
{
    int j, m, sign = 0;
    total = 0;
    
    for (m = 0; element[m] != '\0'; m++); // Size of integer
    
    if(element[0] == '-')
        sign = 1;
    
    for(j = sign; j<m; j++)
    {
        if(element[j] >= '0' && element[j] <= '9')
            total += (element[j] - 48) * power(10, m-1-j);

        else
            return false;
    }

    if(sign == 1)
        total = (-1) * total; // For negative integers

    return true;
}

bool Memory::getTheAddress(int &number, string operand)
{
    string newOp1 = operand.substr(1, operand.size() - 1); // Remove # from the address
    if(convertToNumber(number,newOp1)) // It converts string to integer
        return true;
        
    else
        return false;
}

void Memory::printAll()
{
    for(int i = 0; i < 50; i++)// 50 = default memory size
    {
        cout <<"["<< i <<"] - > ";
        cout << memory[i]<<endl ;
    } 
}

int Memory::power(const int base, const int exp) const
{
    int value = 1;

    if(exp == 0)
        return 1;
    if(base ==0)
        return 0;

    for(int i = 1; i <= exp; i++)
        value = value * base;

    return value;
}