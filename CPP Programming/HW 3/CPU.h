#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define MAX_SIZE 200

class CPU
{
public:
    CPU(); //default constructor
    CPU(string o = "0"); //default argument for constructor
    //prints all the registers and the PC
    void print() const;
    //It returns true if the last instruction executed halted the CPU
    inline bool halted() const { return isHalted; }
    //takes a instruction string, executes it and increases PC
    void execute(string instruction);
    inline int getPC () const { return PC; } //Accessor
    int getRegister(const int index) const   //Accessor  
    {
        return regArr[index];
    }
    
private:
    bool executeWithReturn(string instruction);
    
    //Takes a string and extract op1 and op2
    bool extractOperands(const string & operands, string& op1, string& op2);
    
    //Execute each commands
    bool movCommand(const string & operands);
    bool addCommand(const string & operands);
    bool subCommand(const string & operands);
    int jmpCommand (const string & operands);
    int jpnCommand (const string & operands);
    bool prnCommand(const string & operands);
    
    //Checks the validatiy of registers
    bool isValidReg(const string & operand) const;
    
    //It takes a power
    int power(const int base, const int exp) const;
    
    //Converts to string to an integer
    bool convertToNumber(int &total, const string & element);
    
    inline void setRegister (int index, int value) // Setter for registers
    {
        regArr[index] = value;
    }
    
    const string movStr = "MOV";
    const string addStr = "ADD";
    const string subStr = "SUB";
    const string jmpStr = "JMP";
    const string prnStr = "PRN";
    const string hltStr = "HLT";
    
    int option;
    int regArr[6]; // Array for registers
    int PC; //program counter
    bool isHalted;  
};

#endif /* CPU_H */

