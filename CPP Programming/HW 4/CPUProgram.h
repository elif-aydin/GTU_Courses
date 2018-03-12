#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define MAX_SIZE 200 // max size for file lines

class CPUProgram 
{
public:
    CPUProgram(); //default constructor
    CPUProgram(const string & fileName); 
    CPUProgram(int opt);
    
    // takes an integer and returns a string that contains the program line that corresponds to the integer.
    string getLine(const int num); 
    // returns the number of lines read from the file.
    inline int size() const { return numOfLines; }
    bool ReadFile(const string & fileName); // reads to given file

private:
    bool findNumberOfLines (const string & fileName); //finds number of lines
    
    int numOfLines;
    string lines[MAX_SIZE];
    bool error = false;
    int option;
};

#endif /* CPUPROGRAM_H */