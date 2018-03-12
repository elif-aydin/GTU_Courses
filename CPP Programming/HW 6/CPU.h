#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <string>
#include <fstream>

#include "Memory.h"

using namespace std;

class CPU
{
public:
    CPU(){}
    CPU(string);
    CPU(int);

    //prints all the registers and the PC
    void print() const;
    // It returns true if the last instruction executed halted the CPU
    inline bool halted() const { return isHalted; }
    // Takes a instruction string, executes it and increases PC
    void execute(string, Memory &);
    
    // Getters
    bool getTheAddress(int &, string)const;
    inline int getPC () const { return PC; } 
    inline void setPC(const int pc) { PC = pc; }
    inline int getRegister(const int index) const { return regArr[index]; }
        
private:
    void removeSpaces(string &) const; // remove extra spaces
    void convertToUppercase(string &) const; // convert all letters to uppercase
    
    bool executeWithReturn(string, Memory &);
    //Takes a string and extract op1 and op2
    bool extractOperands(const string &, string &, string &)const;
    
    //Execute each commands
    bool movCommand(const string &, Memory &);
    bool addCommand(const string &, Memory &);
    bool subCommand(const string &, Memory &);
    int jmpCommand (const string &, Memory &) const;
    int jpnCommand (const string &, Memory &) const;
    bool prnCommand(const string &, Memory &) const;
    
    //Checks the validity of registers
    bool isValidReg(const string &) const;
    //It takes a power
    int power(const int, const int) const;
    //Converts to string to an integer
    bool convertToNumber(int &, const string &) const;
    inline void setRegister (int index ,int value) // Setter
    {
        regArr[index] = value;
    }
    
    // Commands
    string movStr = "MOV";
    string addStr = "ADD";
    string subStr = "SUB";
    string jmpStr = "JMP";
    string prnStr = "PRN";
    string hltStr = "HLT";
    string jpnStr = "JPN";

    int option;
    int regArr[6];
    int PC; //program counter
    bool isHalted;  
};

#endif /* CPU_H */

