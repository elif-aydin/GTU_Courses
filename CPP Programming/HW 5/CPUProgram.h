#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


class CPUProgram 
{
public:
    CPUProgram(); //default constructor
    CPUProgram(const string&); 
    CPUProgram(int);

    /*************/
    /**OPERATORS**/
    /*************/
    
    //Takes two programs and returns a new program that appends the second to first one
    CPUProgram operator +(CPUProgram &);
    
    //Prints the program
    friend ostream &operator <<(ostream &, const CPUProgram &);
    
    //Takes an integer and works like getLine. Returns the program line as a string.
    string operator [](const int);
    
    //Takes an instruction line as a string and appends the instruction end of program.
    CPUProgram& operator +=(string);
    
    //Takes a CPUProgram and an inst line as a string. Returns a newCPUProgram that has the original CPUProgram with appended last line from the parameterstring.
    CPUProgram operator +(string);
    
    //Takes two integers and returns a new program that contains the instructions between the given integers.
    CPUProgram operator ()(int, int);
    
    //Post and pre decrement operators - - that delete the last line of the program.
    CPUProgram operator --(int); //Postfix --
    void operator --(); //Prefix --
    
    //Comparison operators
    const bool operator ==(const CPUProgram &)const;
    const bool operator !=(const CPUProgram &)const;
    const bool operator < (const CPUProgram &)const;
    const bool operator <=(const CPUProgram &)const;
    const bool operator > (const CPUProgram &)const;
    const bool operator >=(const CPUProgram &)const;
    
    // takes an integer and returns a string that contains the program line that corresponds to the integer.
    string getLine(const int); 
    // returns the number of lines read from the file.
    inline int size() const { return numOfLines; }
    bool ReadFile(const string &); // reads to given file

private:
    bool findNumberOfLines (const string &); //finds number of lines
    
    vector <string> lines; 
    int numOfLines;
    bool error = false;
    int option;
};

#endif /* CPUPROGRAM_H */