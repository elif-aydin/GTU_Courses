#include "CPU.h"

CPU::CPU(string o) //default argument
{
    int opt;
    if (!convertToNumber(opt, o)) //converts string option to integer option
    {
        cerr << "You entered a wrong input for option. Default value gonna be assigned (which is 0)." << endl;
        opt = 0;
    }
    
    else if (!(opt == 0 || opt == 1))
    {
        cerr << "Options can be only 0 and 1 " << endl;
        cerr << "Default is assigning to 0." << endl;
        opt = 0;
    }
    
    option = opt;
    PC = 1;
    isHalted = false;
    
    for(int i = 0; i< 6; i++)
        regArr[i] = 0;
}

void CPU::execute(string instruction)
{
    if (option == 1)
    {
        cout << endl << instruction << endl;
        print();
    }
    
    bool result = executeWithReturn(instruction);
    if (result == false)
    {
        cerr << "Error" << endl;
        isHalted = true;
    }
    
    PC++;
}

void CPU::print() const
{
    cout << "PC = " << getPC() << endl;
    cout << "R1 = " << getRegister(1) << " " ;
    cout << "R2 = " << getRegister(2) << " " ;
    cout << "R3 = " << getRegister(3) << " " ;
    cout << "R4 = " << getRegister(4) << " " ;
    cout << "R5 = " << getRegister(5) << " " ;
    cout << endl;
}

bool CPU::executeWithReturn(string instruction)
{
    string operands, command ;
    bool result;
    
    command = instruction.substr(0,3);//her komut 3 karakter oldugu icin;
    if (instruction.size()!= command.size())
            operands = instruction.substr(command.size() + 1, instruction.size() - command.size());//ilk 3 command 4 ten itibaren kalanı

    if (command == movStr)
    {   
        result = movCommand(operands);
    }

    else if (command == addStr)
    {
        result = addCommand(operands);
    }

    else if (command == subStr)
    {
        result = subCommand(operands);
    }

    else if (command == jmpStr)
    {
        int temp = jmpCommand(operands);
        if (temp >= 0)
        {
            PC = temp;
            result = true; 
        }
        else if(temp == -2)
           result = false;
        else
            result = true;
    }

    else if (command == prnStr)
    {
        result = prnCommand(operands);
    }

    else if (command == hltStr)
    {
        cout << endl;
        cout << "Program is halting." << endl;
        print();
        isHalted = true;
        result = true;
    }

    else
    {
        cerr << "Invalid command > "<< instruction << endl;
        result = false;
    }
    
    return result;
}

//It checks the validatiy of registers
bool CPU::isValidReg(const string & operand) const
{
    if(operand == "R1" || operand == "R2" || operand == "R3" || operand == "R4" || operand == "R5")
        return true;
    
    else
        return false;
}

bool CPU::movCommand(const string & operands)
{
    string op1, op2;
    extractOperands(operands, op1, op2);
    int number;
    
    if(isValidReg(op1) && isValidReg(op2)) //mov r1, r2
    {
        char a = op1.at(1);
        int index1 = a - '0'; //registerin indexi elde edilir
        
        char b = op2.at(1);
        int index2 = b - '0'; // o arrayin o indisi. mesela r3 deki 3 u alır
        
        setRegister(index2, getRegister(index1)); //op1 in degerini op2 ye kopyalar
        return true;
    }

    if (isValidReg(op1) && convertToNumber(number, op2))
    {
        int number;
        if (convertToNumber(number, op2))
        {
            char a = op1.at(1);
            int index1 = a - '0'; //registerin indexi elde edilir
            setRegister(index1, number);
            return true;
        }
        else
        {
            cerr << "Invalid constant on the line" << endl;
            return false;
        }            
    }
    else
    {
        cout << "error -> " << operands << endl;
        return false;
    }
}

bool CPU::addCommand(const string & operands)
{
    string op1, op2;
    int number;
    extractOperands(operands, op1, op2);

    if (isValidReg(op1) && isValidReg(op2))
    {
        char a = op1.at(1);
        int index1 = a - '0';
        a = op2.at(1);
        int index2 = a - '0';
        int temp = getRegister(index1);       
        setRegister(index1, temp + getRegister(index2));
        
        return true;
    }

    else if (isValidReg(op1) && convertToNumber(number, op2))
    {
        char a = op1.at(1);
        int index1 = a - '0';
        int temp = getRegister(index1);       
        setRegister(index1, temp + number);
        
        return true;
    }
    else
        return false;
}

bool CPU::subCommand(const string & operands)
{
    string op1, op2;
    int number;
    extractOperands(operands, op1, op2);

    if (isValidReg(op1) && isValidReg(op2))
    {
        char a = op1.at(1);
        int index1 = a - '0';
        a = op2.at(1);
        int index2 = a - '0';
        
        int temp = getRegister(index1);
        setRegister(index1,temp - getRegister(index2));
        return true;
    }

    else if (isValidReg(op1) && convertToNumber(number, op2))
    {
        char a = op1.at(1);
        int index1 = a - '0';

        int temp = getRegister(index1);       
        setRegister(index1, temp - number);
        return true;
    }

    else
        return false;
}

int CPU::jmpCommand(const string & operands)
{
    int choice = operands.find(",");

    if (choice == -1) // It means there is no comma on the string
    {
        int a = operands.find(" "); //Returns the place of comma
        if (a == -1)
        {
            a = operands.size();
        }
        
        string op1 = operands.substr(0, a); // r1 = linesaddress             
        int number;

        if (convertToNumber(number, op1))
            return (number - 2); 

        else 
            return -2; //
    }

    else
    {
        string op1, op2;
        extractOperands(operands, op1, op2);

        if (isValidReg(op1))
        {
            char c = op1.at(1);
            int index1 = c - '0'; // o arrayin o indisi. mesela r3 deki 3 u alır

            if(getRegister(index1) == 0)
            {
                int number;
                if (convertToNumber(number, op2))
                    return (number - 2);
                else
                {
                    cerr << "cant convert: " << op2 << endl;
                    return -2;
                }
            }

            else
                return -1;
        }

        else
            return -2;
    }
}

bool CPU::prnCommand(const string & operands)
{
    int a = operands.find(" "); // return of place comma
    string op1 = operands.substr(0, a); // r1 = linesaddress  

    if (isValidReg(op1)) //if register
    {
        char a = op1.at(1);
        int index1 = a - '0'; // o arrayin o indisi. mesela r3 deki 3 u alır

        cout << getRegister(index1) << endl;
        return true;
    }

    else // if is not a register
    {
        int number;

        if (convertToNumber(number, op1)) //convert to number
        {
            cout << number << endl;
            return true;
        }
        else
            return false;
    }
}

int CPU::power(const int base, const int exp) const
{
    int value = 1;

    if(exp == 0)
        return 1;
    if(base ==0)
        return 0;

    for(int i = 1; i <= exp; i++)
        value = value * base;

    return value;
}

bool CPU::convertToNumber(int &total, const string & element)
{
    int j, m, sign = 0;
    total = 0;
    
    for (m = 0; element[m] != '\0'; m++);
    
    if(element[0] == '-')
        sign = 1;
    
    for(j = sign; j<m; j++)
    {
        if(element[j] >= '0' && element[j] <= '9')
            total += (element[j] - 48) * power(10, m-1-j);

        else
            return false;
    }

    if(sign == 1)
        total = (-1) * total;

    return true;
}

bool CPU::extractOperands(const string & operands, string& op1, string& op2) //sabit kalıcak
{
    int a = operands.find(","); // return place of comma
    op1 = operands.substr(0, a); // op1 e bastan a'ya kadar olanı atar.Bu bizim op1 imiz olur. 
    
    //create a new string for parse to op2
    string othersSecond = operands.substr(op1.size()+1, operands.size() - op1.size()); 

    int b = othersSecond.find(" "); //return place of space
    if (b == -1) //if there is no sapce
    {
      b = othersSecond.size();
    }
    
    op2 = othersSecond.substr(0, b); //we take to op2
    
    return true;
}