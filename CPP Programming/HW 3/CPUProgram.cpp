#include "CPUProgram.h"
using namespace std;


CPUProgram::CPUProgram() 
{
    cerr << "No input file given" << endl;  
}

CPUProgram::CPUProgram(string fileName)
{
    if(!(findNumberOfLines(fileName)))
        cerr << "Error on the number of lines" << endl;
   
    readFile(fileName);
}

bool CPUProgram::findNumberOfLines (const string &fileName)
{
    ifstream file(fileName.c_str()); //create a file
    int numberOfLines = 0; //total line number
    string s; //string for getline
    
    if (file.is_open()) // is file open ?
    {
        while(getline(file,s)) // It puts every line to s and returns true if its okay
            numberOfLines ++; // find number of lines
    }
    else
    {
        cerr << "There is no file" << endl;
        return false;
    }
    
    file.close();

    numOfLines = numberOfLines;
    
    return true;
}

bool CPUProgram::readFile(const string &fileName)
{
    ifstream file(fileName.c_str());

    if (file.is_open())
    {
        string temp;
        for(int runningLine = 0; runningLine < numOfLines; runningLine++)
        {
            getline(file, temp);
            int position = temp.find(';'); //ignores after ;
            if (position != -1)
                temp = temp.substr(0, position); //put a new string before ;
            
            lines[runningLine] = temp;           
        }
        return true;
    }
    else
        return false;
}

string CPUProgram:: getLine(const int num)
{
    if (num > numOfLines)
    {
        cout << "You are trying to reach beyond of program!" << endl;
        return "NULL"; // returns a non-command word for finished program with an error
    }
    
    string command = lines[num];
    removeSpaces(command);
    convertToUppercase(command);
    
    return command;
}

void CPUProgram::convertToUppercase(string &line)
{
    for (int i = 0; line[i] != '\0'; i++)
        if(line[i] >= 'a' && line[i] <= 'z')
            line[i] -= 32;
}

void CPUProgram::removeSpaces(string &line)
{   
    int m;    
    // reduce all spaces to 1
    for(m = 0; m < line.size()-1; ++m)
    {
        if(line[m] == ' ' && line [m+1] == ' ')
        {
            line.erase(m+1, 1);
            m = m-1;
        }
    }

    // check if a space in the beginning of the file
    if (line.at(0) == ' ')
    {
        line.erase(0, 1);
    }

    // remove spaces after comma
    for(m = 0; m < line.size()-1; ++m)
    {
        if(line[m] == ',' && line [m+1] == ' ')
            line.erase(m+1, 1);
    }

    // remove spaces before comma
   for(m = 0; m < line.size(); ++m)
    {
        if(line[m] == ',' && line [m-1] == ' ')
            line.erase(m-1, 1);
    }
}