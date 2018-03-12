#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <string>
#include <fstream>
#include "Memory.h"
#include "CPUProgram.h"

using namespace std;
#define MAX_SIZE 200

class CPU
{
public:
    CPU(){}
    CPU(string o);
    CPU(int opt);

    //prints all the registers and the PC
    void print() const;
    //It returns true if the last instruction executed halted the CPU
    inline bool halted() const { return isHalted; }
    //takes a instruction string, executes it and increases PC
    void execute(string instruction, Memory & memory);
    
    // Getters
    bool getTheAddress(int &number, string operand);
    inline int getPC () const { return PC; } 
    inline void setPC(int pc) { PC = pc; }
    inline int getRegister(const int index) const { return regArr[index]; }
        
private:
    void removeSpaces(string &line); // remove extra spaces
    void convertToUppercase(string &line); // convert all letters to uppercase
    
    bool executeWithReturn(string instruction, Memory &memory);
    //Takes a string and extract op1 and op2
    bool extractOperands(const string & operands, string& op1, string& op2);
    
    //Execute each commands
    bool movCommand(const string & operands, Memory & memory);
    bool addCommand(const string & operands, Memory & memory);
    bool subCommand(const string & operands, Memory & memory);
    int jmpCommand (const string & operands, Memory & memory);
    int jpnCommand (const string & operands, Memory & memory);
    bool prnCommand(const string & operands, Memory & memory);
    
    //Checks the validatiy of registers
    bool isValidReg(const string & operand) const;
    //It takes a power
    int power(const int base, const int exp) const;
    //Converts to string to an integer
    bool convertToNumber(int &total, const string & element);
    inline void setRegister (int index, int value) // Setter
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

