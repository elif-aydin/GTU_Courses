#ifndef CPUPROGRAMDYN_H
#define CPUPROGRAMDYN_H


#include <iostream>
#include <string>
#include <fstream>

using namespace std;

namespace HW6
{
    class CPUProgramDyn 
    {
    public:
        CPUProgramDyn(); //default constructor
        CPUProgramDyn(const string &);  //It takes fileName
        CPUProgramDyn(int);

        CPUProgramDyn(const CPUProgramDyn &);

        /*************/
        /**OPERATORS**/
        /*************/

        //Takes two programs and returns a new program that appends the second to first one
        CPUProgramDyn operator + (CPUProgramDyn &);

        //Takes an integer and works like getLine. Returns the program line as a string.
        string operator [](const int) const;

        //Takes an instruction line as a string and appends the instruction end of program.
        CPUProgramDyn& operator +=(string);

        //Takes a CPUProgramDyn and an inst line as a string. Returns a newCPUProgramDyn that has the original CPUProgramDyn with appended last line from the parameterstring.
        CPUProgramDyn operator +(string);

        //Takes two integers and returns a new program that contains the instructions between the given integers.
        CPUProgramDyn operator ()(int, int);

        //Post and pre decrement operators - - that delete the last line of the program.
        CPUProgramDyn operator --(int); //Postfix --
        void operator --(); //Prefix --

        CPUProgramDyn & operator = (const CPUProgramDyn &);

        //Comparison operators
        const bool operator ==(const CPUProgramDyn &) const;
        const bool operator !=(const CPUProgramDyn &) const;
        const bool operator < (const CPUProgramDyn &) const;
        const bool operator <=(const CPUProgramDyn &) const;
        const bool operator > (const CPUProgramDyn &) const;
        const bool operator >=(const CPUProgramDyn &) const;

        //Prints the program
        friend ostream & operator <<(ostream &out, const CPUProgramDyn & P1)
        {
            for(int i = 0; i < P1.size(); i++)
                out << P1[i] << endl;

            return out;
        }

        // Takes an integer and returns a string that contains the program line that corresponds to the integer.
        string getLine(const int) const; 

        // Returns the number of lines read from the file.
        inline int size() const { return currentLine; }
        
        bool ReadFile(const string &); // reads to given file

        void deallocate()
        {
            if (size() != 0)
            {
                delete [] lines;
                currentLine = 0;
                capacity = 0;
            }

        }
        
        ~CPUProgramDyn()
        {
            deallocate();
        }
        
    private:
        int findNumberOfLines (const string &); //finds number of lines
        void reallocate(int newCapacity);
        void init(int opt);
        
        int capacity = 0;
        int currentLine = 0;
        string * lines;
        bool error = false;
        int option;
    };
}

#endif /* CPUPROGRAMDYN_H */
