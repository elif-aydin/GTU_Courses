#ifndef MEMORY_H
#define MEMORY_H

#define MAX_SIZE 200 // Max size for file line
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Memory 
{
public:
    Memory(); // default constructor
    Memory(int opt);
    
    bool getMem(const string , int &); // Getter for memory
    int getMem(const int index) const { return memory[index]; } // Getter for memory
    inline void setMem (const int index, const int value) // Setter for memory
    {
        memory[index] = value;
    }
    
    bool getTheAddress(int &, string); // take the 30 from #30 
    void printAll(); // It prints all memory 
    void initMemory();
    
private:
    bool convertToNumber(int &, const string &); // stoi function
    int  power(const int, const int) const; //power function
 
    unsigned int memory[50]; // memory
    int option;
};

#endif /* MEMORY_H */