/*************************************************************
 *                                                           *
 * HW-02                                                     *
 * Student Name: Elif Seyma ARMAGAN                          *
 * Student ID  : 151044042                                   *
 * Date        : 15.10.2016                                  *
 * Points      : A simple CPU simulation program             *
 *                                                           *
 *************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#define MAX_SIZE 200 //en fazla 200 satir olabilir

using namespace std;

//It take a file as a parameter and find the line number on the file
int findNumberOfLines(string fileName);

//It executes the commands
bool executeCommands(int option, string commands[], int size, int regArr[], int numberOfLines, int memoryArr[]);

//It opens the file and ignores after ;
void readFile(string fileName, string lines[], int numberOfLines);

//It takes a string and extract op1 and op2
bool extractOperands(string operands, string& op1, string& op2);

//Commands
bool movCommand(string operands, int regArr[], int memoryArr[]);
bool addCommand(string operands, int regArr[], int memoryArr[]);
bool subCommand(string operands, int regArr[], int memoryArr[]);
int jmpCommand(string operands, int regArr[], int memoryArr[]);
int jpnCommand(string operands, int regArr[], int memoryArr[]);
bool prnCommand(string operands, int regArr[], int memoryArr[]);

//It checks the validatiy of registers
bool isValidReg(string operand);

//It removes extra spaces on the string
void removeSpaces(string &line);

//It converts all lowercase letters to uppercase
void convertToUppercase(string &line);

//It takes a power
int power(int base, int exp);

//It converts to string to an integer
bool convertToNumber(int &total, string element);

//It prints the registers
void printRegisters(int regArr[]);

//It gives the memory address
bool getTheAddress(int &number, string operand);

void printMemory(int memoryArr[]);

