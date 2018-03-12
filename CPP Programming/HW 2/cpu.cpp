#include "cpu.h"
using namespace std;


// parametre olarak dosyayi alir, acar ve dosyadaki toplam satir sayisini return eder
int findNumberOfLines(string fileName) //sabit kalıcak
{
    ifstream file(fileName.c_str()); //file tipi oluşturma
    int numberOfLines = 0; //toplam line sayisi
    string s; //getline in kullanacagi string
    
    if (file.is_open()) // dosya acildi mi?
    {
        while(getline(file,s)) //her satiri s e atar true doner
            numberOfLines ++; //line sayisini bulmak    
    }
    else
    {
        cerr << "There is no file" << endl;
        return 1;
    }
    
    file.close();

    return numberOfLines;
}

//dosyayi acar okur ve ; den sonrasını ignore eder.
void readFile(string fileName, string lines[], int numberOfLines) //sabit kalıcak
{
    ifstream file(fileName.c_str());

    if (file.is_open())
    {
        string temp;
        // running line = o an islenen satir
        for(int runningLine = 0 ; runningLine < numberOfLines; runningLine++)
        {
            getline(file, temp);            // file da okudugu a satirini o lines in a sina atar
            int position = temp.find(';');  //; den sonrasini ignore etmek
            if (position != -1)
                temp = temp.substr(0, position);
            
            lines[runningLine] = temp;
        }
    }
}

//stringi alır ve icinden op1 ve op2 yi elde eder
bool extractOperands(string operands, string& op1, string& op2) //sabit kalıcak
{

    int a = operands.find(","); // virgulun yerini dondurur a bunu tutar.
    op1 = operands.substr(0, a); // op1 e bastan a'ya kadar olanı atar.Bu bizim op1 imiz olur. 
    
    string othersSecond = operands.substr(op1.size()+1, operands.size() - op1.size()); //op1 den sonrasını parcalamak icin yeni bir stringe atar.

    int b = othersSecond.find(" "); //boslugun bulundugu yeri dondurur.
    if (b == -1) //eger bosluk yoksa
    {
      b = othersSecond.size();
    }
    
    op2 = othersSecond.substr(0, b); //op2 yi elde ederiz
    
    return 
        true;
}

bool executeCommands(int option, string commands[], int size, int regArr[], int numberOfLines, int memoryArr[])
{
    string movStr = "MOV";
    string addStr = "ADD";
    string subStr = "SUB";
    string jmpStr = "JMP";
    string prnStr = "PRN";
    string hltStr = "HLT";
    string jpnStr = "JPN";

    bool result = true;

    for (int i = 0; i < size && result == true; ++i)
    {        
        removeSpaces(commands[i]);
        convertToUppercase(commands[i]);

        if(option == 1)
        {   
            //cout <<endl;
            cout << commands[i]<< endl;
            //printRegisters(regArr);   
        }
        
        if(option == 2)
        {
            //cout<<endl;
            cout << commands[i]<<endl;
            printRegisters(regArr);
            //cout << endl;
            printMemory(memoryArr);
        }
    
	    string operands ;
        string command = commands[i].substr(0,3);//her komut 3 karakter oldugu icin

        if (commands[i].size()!= command.size())
        	operands = commands[i].substr(command.size() + 1, commands[i].size() - command.size());//ilk 3 command 4 ten itibaren kalanı
        
        if (command == movStr)
        {   
            result = movCommand(operands, regArr, memoryArr);
        }

        else if (command == addStr)
        {
            result = addCommand(operands, regArr, memoryArr);
        }

        else if (command == subStr)
        {
            result = subCommand(operands, regArr, memoryArr);
        }

        else if (command == jmpStr)
        {
            int temp = jmpCommand(operands, regArr, memoryArr);
            if (temp >= 0)
            {
                if(temp <= numberOfLines)
                {
                    i = temp;
                    result = true;
                } 
                else
                {
                    cerr << "Invalid jump adress on the line" <<endl;
                return false;        
                }
            }
           else if(temp == -2)
                return false;
        }
        
        else if (command == jpnStr)
        {
            int temp = jpnCommand(operands, regArr, memoryArr);
            if (temp >= 0)
            {
                if(temp <= numberOfLines)
                {
                    i = temp;
                    result = true;
                } 
                else
                {
                    cerr << "Invalid jump adress on the line" <<endl;
                    return false;        
                }
            }
            
            else if(temp == -2)
                return false;
        }

        else if (command == prnStr)
        {
            result = prnCommand(operands, regArr, memoryArr);
        }

        else if (command == hltStr)
        {
            printMemory(memoryArr);
            printRegisters(regArr);
            cout << endl;
            cout << "Program is halting." << endl;
            return true;
        }

        else
        {
            cerr << "Invalid command > "<< commands[i] << endl;
            return false;
        }
    }

    return result;
}

//It checks the validatiy of registers
bool isValidReg(string operand)
{
    if(operand == "R1" || operand == "R2" || operand == "R3" || operand == "R4" || operand == "R5")
        return true;
    
    else
        return false;
}

bool movCommand(string operands, int regArr[], int memoryArr[])
{
    string op1, op2;
    extractOperands(operands, op1, op2);
    int number;

    if(op1.at(0) == '#' && isValidReg(op2)) // mov #30 , r2 durumu
    {
        int memoryAddress;
        if(getTheAddress(memoryAddress, op1))//op1 adres oldugu icin memory adresi belirlenir
        { 
            char a = op2.at(1);
            int index1 = a - '0'; //registerin indexi elde edilir
                
            regArr[index1] = memoryArr[memoryAddress];  
            return true; 
        }
        else
        {
            cerr << "Invalid memory address on the line" << endl;
            return false;
        }
    }

    else if(isValidReg(op1) && op2.at(0) == '#') //mov r1, #30
    {
        int memoryAddress;
        if(getTheAddress(memoryAddress, op2))
        {
            char a = op1.at(1);
            int index1 = a - '0'; //registerin indexi elde edilir
      
            memoryArr[memoryAddress] = regArr[index1];
            return true; 
        }
        else
        {
            cerr << "Invalid memory address on the line" << endl;
            return false;   
        }    
    }

    else if(isValidReg(op1) && isValidReg(op2)) //mov r1, r2
    {
        char a = op1.at(1);
        int index1 = a - '0'; //registerin indexi elde edilir
        
        char b = op2.at(1);
        int index2 = b - '0'; // o arrayin o indisi. mesela r3 deki 3 u alır
        
        regArr[index2] = regArr[index1]; //op1 in degerini op2 ye kopyalar
        return true;
    }

    else if (isValidReg(op1) && convertToNumber(number, op2))
    {
        int number;
        if (convertToNumber(number, op2))
        {
            char a = op1.at(1);
            int index1 = a - '0'; //registerin indexi elde edilir
            regArr[index1] = number;
            return true;
        }
        else
        {
            cerr << "Invalid constant on the line" << endl;
            return false;
        }            
    }

    else if (op1.at(0) == '#' && convertToNumber(number, op2))
    {
        int memoryAddress;
        if(getTheAddress(memoryAddress, op1))
        {
            memoryArr[memoryAddress] = number; //const degerin memory ye atilması
            return true;
        }
        else
        {
            cerr << "Invalid number on the file > " << op2 <<  "is not an integer" << endl;
            return false;
        }
    }

    else
    {
        cout << "error -> " << operands << endl;
        return false;
    }
}

bool addCommand(string operands, int regArr[], int memoryArr[])
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

        regArr[index1] += regArr[index2];
        return true;
    }

    else if (isValidReg(op1) && convertToNumber(number, op2))
    {
        char a = op1.at(1);
        int index1 = a - '0';

        regArr[index1] += number;
        return true;
    }

    else if (isValidReg(op1) && op2.at(0) == '#')
    {
        char a = op1.at(1);
        int index1 = a - '0';

        int memoryAddress;
        if(getTheAddress(memoryAddress, op2))
        {
            regArr[index1] += memoryArr[memoryAddress];
            return true;
        }
        else
            return false;
    }

    else
        return false;
}

bool subCommand(string operands, int regArr[], int memoryArr[])
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

        regArr[index1] -= regArr[index2];
        return true;
    }

    else if (isValidReg(op1) && convertToNumber(number, op2))
    {
        char a = op1.at(1);
        int index1 = a - '0';

        regArr[index1] -= number;
        return true;
    }

    else if (isValidReg(op1) && op2.at(0) == '#')
    {
        char a = op1.at(1);
        int index1 = a - '0';

        int memoryAddress;
        if(getTheAddress(memoryAddress, op2))
        {
            regArr[index1] -= memoryArr[memoryAddress];
            return true;
        }
        else
            return false;
    }

    else
        return false;
}

//only parse jmp command ve sayiyi elde eder
int jmpCommand(string operands, int regArr[], int memoryArr[])
{
    int choice = operands.find(",");

    if (choice == -1) // virgül yok demek
    {
        int a = operands.find(" "); //  , un yerini dondurur a bunu tutar.
        string op1 = operands.substr(0, a); // r1 = linesadress             
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

            if(regArr[index1] == 0)
            {
                int number;
                if (convertToNumber(number, op2))
                    return (number - 2);
                else
                    return -2;
            }

            else
                return -1;
        }

        else
            return -2;
    }
}

int jpnCommand(string operands, int regArr[], int memoryArr[])
{
    string op1, op2;
    extractOperands(operands, op1, op2);

    if (isValidReg(op1))
    {
        char c = op1.at(1);
        int index1 = c - '0'; // o arrayin o indisi. mesela r3 deki 3 u alır

        if(regArr[index1] <= 0)
        {
            int number;
            if (convertToNumber(number, op2))
                return (number - 2);
            else
                return -2;
        }

        else
            return -1;
    }

    else
        return -2;
}

bool prnCommand(string operands, int regArr[], int memoryArr[])
{
    int a = operands.find(" "); //  , un yerini dondurur a bunu tutar.
    string op1 = operands.substr(0, a); // r1 = linesadress  

    if (isValidReg(op1)) //eger register ise
    {
        char a = op1.at(1);
        int index1 = a - '0'; // o arrayin o indisi. mesela r3 deki 3 u alır

        cout << regArr[index1] << endl;
        return true;
    }
    
    else if(op1.at(0) == '#') //eger memory adresi ise
    {
       int address;
       getTheAddress(address,op1);
       cout << memoryArr[address] << endl;
       return true;
    }

    else //ustteki ikisi degilse o zaman sayidir
    {
        int number;

        if (convertToNumber(number, op1))
        {
            cout << number << endl;
            return true;
        }
        else
            return false;
    }
}

//my power program
int power(int base, int exp)
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

//my stoi program
bool convertToNumber(int &total, string element)
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

//Remove extra spaces on the line
void removeSpaces(string &line)
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

//Converts the string to upperCase
void convertToUppercase(string &line)
{
    for (int i = 0; line[i] != '\0'; i++)
        if(line[i] >= 'a' && line[i] <= 'z')
            line[i] -= 32;
}

//Register iceriklerini ekrana basar
void printRegisters(int regArr[])
{
    cout << endl;
    cout << "R1 = " << regArr[1] << " " ;
    cout << "R2 = " << regArr[2] << " " ;
    cout << "R3 = " << regArr[3] << " " ;
    cout << "R4 = " << regArr[4] << " " ;
    cout << "R5 = " << regArr[5] << " " ;
    cout<<endl;
}

void printMemory(int memoryArr[])
{
    for(int i = 1; i <= 50; i++)// 50 = default memory size
    {
        cout << memoryArr[i-1] << "| " ;
        if(i % 10 == 0 )
            cout << endl;
    } 
}

bool getTheAddress(int &number, string operand)
{
    string newOp1 = operand.substr(1, operand.size() - 1); //adresin basindaki # atilararak sadece int hali elde edilir
    if(convertToNumber(number,newOp1)) //string olan sayi int e cevrilir
        return true;
        
    else
        return false;
}