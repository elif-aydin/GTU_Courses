/*************************************************************
 *                                                           *
 * HW07 Part1                                                *
 * Student Name: Elif Seyma ARMAGAN                          *
 * Student ID  : 151044042                                   *
 * Date        : 12.04.2016                                  *
 * Points      : Verilen bir string in palindrome olup       *
 *               olmadigini kontrol eden program             *
 *			                                                 *
 *                                                           *
 *************************************************************/


#include <stdio.h>


/* Prototiplerin tanitilmasi */
int isPalindrome(char * str);
int findPalindrome(int leftIndex, int rightIndex, char *str);
int strLength(char * arr);
int isPunctation(char ch);

int main()
{
	int x;
	char * str;
	
	str = ("a%+^^++%&/&(bc+-//?)(&/% c+-----b)a");
	x = isPalindrome(str);
	
	printf("%d\n", x);
	return 0;
}


int findPalindrome(int leftIndex, int rightIndex, char *str)
{

	int leftChar,rightChar,result;
	char * ptr;

	result = 1;
	ptr = str;
	
	if(leftIndex == rightIndex)
		result = 1;

	else
	{
		leftChar = ptr[leftIndex];
		rightChar = ptr[rightIndex];

		if(isPunctation(leftChar) && (leftIndex+1 <= rightIndex))
			result = findPalindrome(leftIndex+1,rightIndex,str);
	
		else if(isPunctation(rightChar) && (leftIndex <= rightIndex-1))
			result = findPalindrome(leftIndex, rightIndex-1,str);

		else
		{
			if(leftChar >='A' && leftChar <= 'Z')
				leftChar = leftChar + 32; /* 32 ekleyerek lower halini elde ederiz */

			if(rightChar >= 'A' && rightChar <= 'Z')	
				rightChar = rightChar + 32; /* 32 ekleyerek lower halini elde ederiz */
			
			if (leftChar != rightChar)
				result = 0;
			else
			{
				if (leftIndex+1 < rightIndex-1)
					result = findPalindrome(leftIndex+1,rightIndex-1,str);

				else 
					result = 1;
			}
		}		
	}
	return result;	 
}

int isPunctation(char ch)
{
	if(ch < 'A' || ch > 'z' || (ch > 'Z' && ch < 'a'))
	{
		
		return 1;
	}

	return 0; 
}

int isPalindrome(char * str)
{
 	int result,len;

 	if(str == NULL)
 		result = 0;

 	len = strLength(str);

 	result = findPalindrome(0,len-1,str);

 	if(result == 1)
 		result = 1;
 	else if (result == 0)
 		result = 0;

 	return (result);
}


int strLength(char * arr)
{
	int i;
	
	for(i = 0; arr[i] != '\0'; i++) {}

	return i;
}