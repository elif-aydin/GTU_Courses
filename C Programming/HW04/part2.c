/******************************************************************
 * HW04 Part2 Elif Seyma Armagan 151044042                        *
 * ______________________________________	                      *
 * HW04  Part2                                                    *
 * Student Name: Elif Seyma ARMAGAN                               *
 * Student ID  : 151044042                                        * 
 * Date        : 04/03/2016                                       *
 * ______________________________________                         *
 * Description:                                                   *
 *             		                                              *  
 *****************************************************************/

/* Kutuphanelerin tanitilmasi */
#include <stdio.h>

/* Prototipler */
int printNumber(int num, int borderWidth, char chr);
void getInputs(int* num, int* borderWidth, char* chr);
int getNumberOfDigits(int num, int* reversed);
int printBanner(int borderWidth, char chr, int length);

int main()
{  
	/* Start of Main */
	int num,borderWidth;
	char chr;

	getInputs(&num,&borderWidth,&chr);
	printNumber(num, borderWidth, chr);
  	return (0);
  	/* End of Main */
 }

void getInputs(int* num, int* borderWidth, char* chr)
{
	while (1)
	{	
		scanf("%d %d %1c",num, borderWidth,chr);
		if (*num < 0) return;
			printNumber(*num, *borderWidth, *chr);
	}	
}

int getNumberOfDigits(int num, int* reversed)
{   
	int temp,digit;

	temp=num;
	*reversed=0;
	digit=0;
	
	while (temp > 0)
 	{   
	 	*reversed=*reversed*10;
        *reversed=*reversed+temp%10;
        temp=temp/10;
        digit++;
 	}
 	return (digit);
}

int printNumber(int num, int borderWidth, char chr)
{
	int reversedNum,length,i,temp,j,k;
	int numberOfDigits;
	
	numberOfDigits = getNumberOfDigits(num,&reversedNum);
	length=(7 * numberOfDigits) + (2 * borderWidth);
				
	if (num < 100000 && num >=0)
	{	
		printBanner(borderWidth,chr,length);	
		for (i=0; i<7; i++){
			temp = reversedNum;
			for (k=0; k<borderWidth; k++)		
				printf("%1c",chr);	
			for(k=0; k<numberOfDigits; k++)
			{		
				j = temp % 10;
				temp=temp / 10;
				if (i==0 ||  i==6) 
					printf("       ");
				else if ((i==2&& (j==5 || j==6))||
						(i==4 && j ==2)) 
					printf("  %1c    ",chr);
				else if (i==2 && j==1) printf("  %1c%1c   ",chr,chr);
				else if ((i==1&& (j==0||j==2||j==3||j==5||j==6||j==7||j==8||j==9)) ||
						 (i==3&& (j==2||j==4||j==5||j==6||j==8||j==9)) ||
						 (i==5&& (j==0||j==1||j==2||j==3||j==5||j==6||j==8||j==9)) )
					printf("  %1c%1c%1c  ",chr,chr,chr);
				else if ((i==1&&j==4) ||
					     (i==2&&(j==0||j==4||j==8||j==9))||
					     (i==3&&j==0)||
					     (i==4&&(j==0||j==6||j==8)))
					printf("  %1c %1c  ",chr,chr);
				else if (j==1&&(i==1||i==3||i==4))
					printf("   %1c   ",chr);
				else if (i==3 && j==3)
					printf ("   %1c%1c  ",chr,chr);
				else if ((i==2&&(j==2||j==3||j==7))||
						 (i==3&&j==7)||
						 (i==4&&(j==3||j==4||j==5||j==7||j==9))||
						 (i==5&&(j==4||j==7)))
					printf("    %1c  ",chr);
			}	
			for (k=0; k<borderWidth; k++)			printf("%1c",chr);printf("\n");		
		}
		printBanner(borderWidth,chr,length);
		return (1);		
	}
	else return (0);
}

int printBanner(int borderWidth, char chr, int length)
{
	int i,j;

	for(i=0; i<borderWidth; i++)
	{
		for(j=0; j<length; j++)
		printf("%1c",chr);
		printf("\n");
	}
	return (0);
}