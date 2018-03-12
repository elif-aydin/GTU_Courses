#include "CPUProgramDyn.h"

using namespace std;
using namespace HW6;

CPUProgramDyn::CPUProgramDyn() : CPUProgramDyn(0)
{
    
}

CPUProgramDyn::CPUProgramDyn(int opt)
{
    init(opt);
}

CPUProgramDyn::CPUProgramDyn(const string & fileName)
{
    init(0);
    ReadFile(fileName);
}

CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn & other)
{
    (*this) = other; //Zaten = opeatorunu overload ettigimiz icin bu islem sonucu bizim overload ettigimiz = operatoru calisacaktir.
}

void CPUProgramDyn::init(int opt)
{
    option = opt;
    error = true;
}

void CPUProgramDyn::reallocate(int newCapacity) 
{ 
    string * newArr;
    newArr = new string[newCapacity];
    
    for (int i = 0; i < size(); ++i)
        newArr[i] = lines[i];
    
    if (size() != 0)
        delete [] lines;
        
    lines = newArr;
    capacity = newCapacity;   
}

CPUProgramDyn & CPUProgramDyn:: operator =(const CPUProgramDyn & other)
{
    deallocate();

    this->error = other.error;
    this->option = other.option;


    for(int i = 0; i < other.size(); i++)
    {
        (*this) += other[i];

    }    

    return *this;
}

CPUProgramDyn CPUProgramDyn::operator + (CPUProgramDyn& P1)
{
    CPUProgramDyn P2(this->option);
    P2.error = false;
    
    for(int i = 0; i< P1.size(); i++)
        P2 += P1[i];

    for(int i = 0; i< this->size(); i++)
        P2 += (*this)[i];

    return P2;
}

string CPUProgramDyn::operator [](const int index) const
{
    int temp = index;// - 1;  // Array imiz 0 dan basladigi icin

    if (temp >= this->currentLine || temp < 0)
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

CPUProgramDyn CPUProgramDyn::operator + (string inst)
{
    CPUProgramDyn P2;
    for(int i =0 ; i < this->size(); ++i)
        P2 += this->lines[i];
    
    P2.error = false;
    P2 += inst;

    return P2;
}

CPUProgramDyn CPUProgramDyn::operator ()(int start, int end)
{
    CPUProgramDyn P1;
    P1.error = false;

    for (int i = start-1; i < end; i++)
        P1 += this->lines[i];

    return P1;
}


CPUProgramDyn& CPUProgramDyn::operator +=(string inst)
{
    if(this->size() >= capacity)
    {
        reallocate(capacity != 0 ? (capacity*2) : 10);
    }
    
    if (inst != "")
    {
        this->lines[currentLine] = inst;
        this->currentLine++;
    }

    else 
    {
        cerr << "You can't add an empty string to the program" << endl;
    }

    return *this;
}

CPUProgramDyn CPUProgramDyn::operator --(int) //Postfix --
{
    if(this->currentLine <= 0)
    {
        cerr << " The program has no lines. So can't delete a line on the program" << endl;
        return *this;
    }    
    else
    {
        CPUProgramDyn P1;

        for(int i = 0; i < this->size(); i++)
            P1 += this->lines[i];

        this->currentLine --;
        return P1;
    }    
}

void CPUProgramDyn::operator --() //Prefix --
{
    if(this->currentLine <= 0)
        cerr << " The program has no lines. So can't delete a line on the program" << endl;
    else
    {
        this->currentLine--;
    }
}

const bool CPUProgramDyn::operator ==(const CPUProgramDyn& P1) const
{
    if(P1.size() == this->size())
        return true;
    else 
        return false;
}

const bool CPUProgramDyn::operator!= (const CPUProgramDyn& P1) const
{
    if(P1.size() != this->size())
        return true;
    else 
        return false;
}

const bool CPUProgramDyn::operator < (const CPUProgramDyn& P1) const
{
    if(this->size() < P1.size())
        return true;
    else 
        return false;
}

const bool CPUProgramDyn::operator > (const CPUProgramDyn& P1) const
{
    if(this->size() > P1.size())
        return true;
    else 
        return false;
}

const bool CPUProgramDyn::operator >=(const CPUProgramDyn& P1) const 
{
    if(this->size() >= P1.size())
        return true;
    else 
        return false;
}

const bool CPUProgramDyn::operator <=(const CPUProgramDyn& P1) const 
{
    if(this->size() <= P1.size())
        return true;
    else 
        return false;
}

int CPUProgramDyn::findNumberOfLines (const string &fileName)
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

        return -1;
    }

    file.close();
    error = false;
    return numberOfLines;
}

bool CPUProgramDyn::ReadFile(const string & fileName)
{
    int numOfLines = findNumberOfLines(fileName);
    
    if (numOfLines == -1)
        return false;
    
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
            
            (*this) += temp; // Use += to handle this job(like push_back)
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

string CPUProgramDyn::getLine(const int num) const
{
    return (*this)[num];
}    
