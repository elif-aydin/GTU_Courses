/*************************************************************
 *                                                           *
 * HW-01                                                     *
 * Student Name: Elif Seyma ARMAGAN                          *
 * Student ID  : 151044042                                   *
 * Date        : 05.11.2016                                  *
 * Points      : A simple CPU simulation program             *
 *                                                           *
 *************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#define MAX_SIZE 256

using namespace std;

int power(int base, int exp);
bool convertToNumber(int &total, string element);
void readFile(string fileName, string lines[], int numberOfLines);
int findNumberOfLines(string fileName);
bool executeCommands(int option, string commands[], int size, int regArr[], int numberOfLines);
bool extractOperands(string operands, string& op1, string& op2);
bool movCommand(string operands, int regArr[]);
bool addCommand(string operands, int regArr[]);
bool subCommand(string operands, int regArr[]);
int jmpCommand(string operands, int regArr[]);
bool prnCommand(string operands, int regArr[]);
bool isValidReg(string operand);
void removeSpaces(string &line);
void convertToUppercase(string &line);
void printRegisters(int regArr[]);


//3 parametre var mi kontrolu, satir sayisi bulan, dosya okuyan ve komutlari uygulayan fonksiyonu cagirir.
int main(int argc, char** argv) 
{
    if(argc != 3)
    {
        cerr << "You have to enter 3 parameters" << endl;
        return -1
    }
    //file daki toplam satir sayisini bulmak icin fonksiyonu cagirir.
    int numberOfLines = findNumberOfLines(argv[1]);
    
    int option = 0;
    if (convertToNumber(option, argv[2]) == false)
    {
        cerr << "You have to write option as an int!" << endl;
        return -1;
    }
    if (!(option == 0 || option == 1)) 
    {
        cerr << "There are only two options: 0 and 1." << endl;
        return -1;
    }

    string lines[MAX_SIZE];
    readFile(argv[1], lines, numberOfLines);
    
    int regArr[6] = {0}; // en fazla 5 reg olabilir. Uygulamak kolay olsun diye 0 ignore edilir. 1. eleman r1 olur
    bool result = executeCommands(option, lines, numberOfLines, regArr, numberOfLines);
    
    if (result == true)
    {
        cout <<"Program finished succesfully"<<endl;
        return 0;
    }

    else
    {   
        cerr << "Program finished with an error"<<endl;
        return 1;
    }
}

// parametre olarak dosyayi alir ve dosyadaki toplam satir sayisini return eder
int findNumberOfLines(string fileName)
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

void readFile(string fileName, string lines[], int numberOfLines)
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

bool executeCommands(int option, string commands[], int size, int regArr[], int numberOfLines)
{
    string movStr = "MOV";
    string addStr = "ADD";
    string subStr = "SUB";
    string jmpStr = "JMP";
    string prnStr = "PRN";
    string hltStr = "HLT";

    bool result = true;

    for (int i = 0; i < size && result == true; ++i)
    {        
        removeSpaces(commands[i]);
        convertToUppercase(commands[i]);

        if(option == 1)
        {   
            cout<<endl;
            cout << commands[i]<<endl;
            printRegisters(regArr);
            
        }
		string operands ;
        string command = commands[i].substr(0,3);//her komut 3 karakter oldugu icin
        if (commands[i].size()!=command.size())
        	operands = commands[i].substr(command.size() + 1, commands[i].size() - command.size());//ilk 3 command 4 ten itibaren kalanı
        	
        
        if (command == movStr)
        {   
            result = movCommand(operands, regArr);
        }

        else if (command == addStr)
        {
            result = addCommand(operands, regArr);
        }

        else if (command == subStr)
        {
            result = subCommand(operands, regArr);
        }

        else if (command == jmpStr)
        {
            int temp = jmpCommand(operands, regArr);
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
            result = prnCommand(operands, regArr);}

        else if (command == hltStr)
        {
            printRegisters(regArr);
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

bool extractOperands(string operands, string& op1, string& op2)
{

    int a = operands.find(","); //  , un yerini dondurur a bunu tutar.
    op1 = operands.substr(0, a); // r1 e bastan a y kadar olanı atar
    
    string othersSecond = operands.substr(op1.size()+1, operands.size() - op1.size());

    int b = othersSecond.find(" ");
    if (b == -1)
    {
      b = othersSecond.size();
    }
    
    op2 = othersSecond.substr(0, b);
    return true;
}

bool movCommand(string operands, int regArr[])
{
    string op1, op2;
    extractOperands(operands, op1, op2);

    if (isValidReg(op1))
    {
        char a = op1.at(1);
        int index1 = a - '0';

        if(isValidReg(op2))
        {
            a = op2.at(1);
            int index2 = a - '0'; // o arrayin o indisi. mesela r3 deki 3 u alır
            regArr[index2] = regArr[index1];
            return true;
        }
        else //if(r2.at(0) == "R" && (r2.at(1) >= 6 || r2.at(1) <= 0))
        {
            int number;
            if (convertToNumber(number, op2))
            {
                regArr[index1] = number;
                return true;
            }
            else
                return false;
        }
    }

    else
        return false;
}

bool addCommand(string operands, int regArr[])
{
    string op1, op2;
    extractOperands(operands, op1, op2);

    if (isValidReg(op1))
    {
        char a = op1.at(1);
        int index1 = a - '0';

        if(isValidReg(op2))
        {
            a = op2.at(1);
            int index2 = a - '0'; // o arrayin o indisi. mesela r3 deki 3 u alır
            regArr[index1] += regArr[index2];
            return true;
        }
        else
        {
            int number;
            if (convertToNumber(number, op2))
            {
                regArr[index1] += number;
                return true;
            }
            else
                return false;
        }
    }

    else
        return false;
}

bool subCommand(string operands, int regArr[])
{
    string op1, op2;
    extractOperands(operands, op1, op2);

    if (isValidReg(op1))
    {
        char a = op1.at(1);
        int index1 = a - '0';

        if(isValidReg(op2))
        {
            a = op2.at(1);
            int index2 = a - '0'; // o arrayin o indisi. mesela r3 deki 3 u alır
            regArr[index1] -= regArr[index2];
            return true;
        }
        else //if(r2.at(0) == "R" && (r2.at(1) >= 6 || r2.at(1) <= 0))
        {
            int number;
            if (convertToNumber(number, op2))
            {
                regArr[index1] -= number;
                return true;
            }
            else
                return false;
        }
    }

    else
        return false;
}

//only parse jmp command ve sayiyi elde eder
int jmpCommand(string operands, int regArr[])
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

bool prnCommand(string operands, int regArr[])
{
    int a = operands.find(" "); //  , un yerini dondurur a bunu tutar.
    string op1 = operands.substr(0, a); // r1 = linesadress  

    if (isValidReg(op1))
    {
        char a = op1.at(1);
        int index1 = a - '0'; // o arrayin o indisi. mesela r3 deki 3 u alır

        cout << regArr[index1] << endl;
        return true;
    }

    else 
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

//It checks the validatiy of registers
bool isValidReg(string operand)
{
    if(operand == "R1" || operand == "R2" || operand == "R3" || operand == "R4" || operand == "R5")
        return true;
    else
        return false;
}

//my power program
int power(int base, int exp)
{
    int value = 1;
    int i;

    if(exp == 0)
        return 1;
    if(base ==0)
        return 0;

    for(i = 1; i <= exp; i++)
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
            total += (element[j]-48) * power(10,m-1-j);

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
    //remove beginning spaces
    int j=0,k=0,m;

    for (m = 0; line[m] != '\0'; m++); // Line stringinin boyu=m
    while (line[0] == ' ' &&  j<m){
        if (line[0]== ' ' && line[j] != ' ') 
        {
            for (k = 0; j+k<m; k++)
                line[k] = line[j+k];
            line[k] = '\0'; //mark the end of string
        }
        j++;
    }
    k=0;
    
    //1 den fazla boslugu 1e indirme
    for (m = 0; line[m] != '\0'; m++);
    while (k+1 < m)
    {
        if (line[k] == ' ' && line[k+1] == ' ')
        {
            for (j = 0; j+k+2 < m; j++)
                line[k+1+j] = line[k+2+j];
            
            line[k+1+j] = '\0';//mark the end of string
            m--;
        }
        else
            k++;
    }
    
    // remove space after  ","
    k = 0;
    for (m = 0; line[m] != '\0'; m++);
    while (k+2 < m)
    {
        if (line[k] == ',' && line[k+1] == ' ')
        {
            for (j=0; j+k+2 < m; j++)
                line[k+1+j] = line[k+2+j];
            
            line[k+1+j] = '\0';//mark the end of string
            m--;
        }
        else 
            k++;
    } 
    
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
     cout << "R1 = " << regArr[1] << " " ;
     cout << "R2 = " << regArr[2] << " " ;
     cout << "R3 = " << regArr[3] << " " ;
     cout << "R4 = " << regArr[4] << " " ;
     cout << "R5 = " << regArr[5] << " " ;
     cout<<endl;
}