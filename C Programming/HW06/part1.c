#include <stdio.h>
void freq(char* str, int* fr);



int main()
{

	int fr[37],i;
	freq("abCd Ef ghIj kLM nopr stuv yzwxq 123 4 5 6 7 890 00 ?? |",fr);

	for (i=0; i<37; i++)
		printf("%d\n",fr[i]);	
	return 0;
}

void freq(char* str, int* fr)
{
	int i, lowerCase, upperCase, number;
	
    for (i=0;i<37;i++) 
		
        fr[i]=0; /* initialize */
    	i=0;

    while (str[i] != '\0') 
    {
    	lowerCase = str[i] - 'a'; /* a = 97 ascii */
    	upperCase = str[i] - 'A'; /* A = 65 asci */
    	number = str[i] - '0'; /* 0 = 48 ascii */

        if (lowerCase >=0 && lowerCase <= 26)
            fr[lowerCase]++;
        
        else if (upperCase>=0 && upperCase<=26)
            fr[upperCase]++;
       
        else if (number >=0 && number<=9)
            fr[26+number]++;
       
        else 
            fr[36]++ ;
            i++;
    }
}