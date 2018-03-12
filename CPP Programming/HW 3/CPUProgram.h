#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define MAX_SIZE 200 // max size for file lines

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

class CPUProgram 
{
public:
    CPUProgram(); //default constructor
    CPUProgram(string fileName); 
    // takes an integer and returns a string that contains the program line that corresponds to the integer.
    string getLine(const int num); 
    // returns the number of lines read from the file.
    inline int size() const { return numOfLines; } 
    
private:
    string lines[MAX_SIZE];
    int numOfLines;
    
    bool findNumberOfLines (const string & fileName); //finds number of lines
    bool readFile(const string &fileName); // reads to given file
    void removeSpaces(string &line); // remove extra spaces
    void convertToUppercase(string &line); // convert all letters to uppercase
};

#endif /* CPUPROGRAM_H */

