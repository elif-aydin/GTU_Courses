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

CPUProgram CPUProgram::operator +(CPUProgram& P1)
{
    CPUProgram P2;
    for(int i = 0; i< P1.size(); i++)
        P2.lines.push_back(P1.lines[i]);
    
    for(int i = 0; i< this->size(); i++)
        P2.lines.push_back(this->lines[i]);

    P2.numOfLines = P1.numOfLines + this->numOfLines;
    P2.error = false;
    return P2;
}

ostream &operator <<(ostream &out, const CPUProgram & P1)
{
    for(int i = 0; i < P1.size(); i++)
        out << P1.lines[i] << endl;
    return out;
}

string CPUProgram::operator [](const int index)
{
    int temp = index;// - 1;  // Array imiz 0 dan basladigi icin
    
    if (temp >= numOfLines || temp < 0)
    {
        cerr << "You are trying to reach beyond of program! Returning NULL..." << endl;
        return "NULL"; // returns a non-command word for finished program with an error
    }
    
    else if (error)
    {
        cerr <<"There is an error. Returning NULL..." << endl;
        return "NULL";
    }
    
    else
    {
        return lines[temp];
    } 
}

CPUProgram CPUProgram::operator +(string inst)
{
    CPUProgram P2;
    for(int i =0 ; i < this->size(); ++i)
        P2.lines.push_back(this->lines[i]); 
    
    P2.numOfLines = P2.lines.size();
    P2.error = false;
    
    P2 += inst;
    
    return P2;
}

CPUProgram CPUProgram::operator ()(int start, int end)
{
	if(start > this->numOfLines || end > this->numOfLines || start < 0 || end < 0 || start > end)
	{
		CPUProgram emptyObject;
		cerr << "Given interval is not exist in the program. Returning an empty object" << endl;

		return emptyObject;
	}
	else
	{
	    CPUProgram P1;
	    
	    for (int i = start-1; i < end; i++)
	        P1.lines.push_back(this->lines[i]);
	    
	    P1.numOfLines = P1.lines.size();
	    return P1;
	}
    
}

CPUProgram& CPUProgram::operator +=(string inst)
{
    if (inst != "")
    {
        this->lines.push_back(inst);
        this->numOfLines++;
    }
    
    else 
    {
        cerr << "You can't add an empty string to the program" << endl;
    }
    
    return *this;
}

CPUProgram CPUProgram::operator --(int) //Postfix --
{
    if(this->numOfLines < 0)
    {
        cerr << " The program has no lines. So can't delete a line on the program" << endl;
        return *this;
    }    
    else
    {
        CPUProgram P1;

        for(int i = 0; i < this->size(); i++)
            P1.lines.push_back(this->lines[i]);

        P1.numOfLines = this->size();
        lines.pop_back();
        this->numOfLines--;

        return P1;
    }    
}

void CPUProgram::operator --() //Prefix --
{
    if(this->numOfLines < 0)
        cerr << " The program has no lines. So can't delete a line on the program" << endl;
    else
    {
        lines.pop_back();
        this->numOfLines--;
    }
}

const bool CPUProgram::operator ==(const CPUProgram& P1) const
{
    if(P1.size() == this->size())
        return true;
    else 
        return false;
}

const bool CPUProgram::operator!= (const CPUProgram& P1) const
{
    if(P1.size() != this->size())
        return true;
    else 
        return false;
}

const bool CPUProgram::operator < (const CPUProgram& P1) const
{
    if(this->size() < P1.size())
        return true;
    else 
        return false;
}

const bool CPUProgram::operator > (const CPUProgram& P1) const
{
    if(this->size() > P1.size())
        return true;
    else 
        return false;
}

const bool CPUProgram::operator >=(const CPUProgram& P1) const 
{
    if(this->size() >= P1.size())
        return true;
    else 
        return false;
}

const bool CPUProgram::operator <=(const CPUProgram& P1) const 
{
    if(this->size() <= P1.size())
        return true;
    else 
        return false;
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
            int position = temp.find(';'); // Ignores after ;
            if (position != -1)
                temp = temp.substr(0, position); // Put a new string before ;
             lines.push_back(temp);
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
