#include "CPUProgram.h"
using namespace std;

CPUProgram::CPUProgram() 
{
    error = true;
    numOfLines = 0;
}

CPUProgram::CPUProgram(int opt) 
{
    option = opt;
    error = true;
    numOfLines = 0;
}

CPUProgram::CPUProgram(const string & fileName)
{
    if(!(findNumberOfLines(fileName)))
        cerr << "Error on the number of lines" << endl;
   
    ReadFile(fileName);
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
        error = true;

        return false;
    }
    
    file.close();
    error = false;
    numOfLines = numberOfLines;
    return true;
}

bool CPUProgram::ReadFile(const string & fileName)
{
    if(numOfLines == 0)
    {
        findNumberOfLines(fileName);
    }  
    
    ifstream file(fileName.c_str());

    if (file.is_open())
    {
        string temp;
        for(int runningLine = 0; runningLine < numOfLines; runningLine++)
        {
            getline(file, temp);
            int position = temp.find(';'); // ignores after ;
            if (position != -1)
                temp = temp.substr(0, position); // put a new string before ;
            
            lines[runningLine] = temp; 
        }

        error = false;
        return true;
    }
    else
    {
        error = true;
        return false;
    }
}

string CPUProgram::getLine(const int num)
{
	int temp = num;// - 1;  // Array imiz 0 dan basladigi icin
    if (temp > numOfLines || temp < 0)
    {
        cout << "You are trying to reach beyond of program!" << endl;
        return "NULL"; // returns a non-command word for finished program with an error
    }
    
    else if (error)
    {
        return "NULL";
    }
    
    else
    {
        return lines[temp];
    }
}
