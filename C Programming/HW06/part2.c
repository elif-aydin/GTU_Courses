c/*************************************************************
 *                                                           *
 * HW06 Part2                                                *
 * Student Name: Elif Seyma ARMAGAN                          *
 * Student ID  : 151044042                                   *
 * Date        : 09.04.2016                                  *
 * Points      : Bu programin amaci verilen bir string       *
 *			     icerisinde                                  *
 *                                                           *
 *************************************************************/

#include <stdio.h>

/* Prototiplerin tanitilmasi */
int myLen(char * arr);
char* matcher(char* haystack, char* needle);


int main()
{
	char* elif = matcher("elif elif elif   ", "ee");
	printf("%s\n", elif);

	return 0;
}

char* matcher(char* haystack, char* needle)
{
	int i,bul,j,haystackLen,needleLen;
	char* ptr =NULL;
	
	if (haystack == NULL || needle == NULL)
		return ptr;

	bul=0;
	haystackLen = myLen(haystack);
    needleLen = myLen(needle);

	i=0;
	if (haystackLen >= needleLen)
	{
		while(haystack[i] != '\0' && bul==0)
		{
		    j = 0;
		    bul = 1;
			
		    if(needleLen+i>haystackLen)
			    return NULL;
			else   
			    ptr = &haystack[i];
		
			while(needle[j] != '\0' && bul==1)
			{	
				if(needle[j] != haystack[i] && j%2==0 && i%2==0 )
				{
					bul=0;
					ptr=NULL;	
				}
			 	j=j+1;
			 	i=i+1;			 		
		    }i=i+1; 
	    }
	}
 	return ptr;
}

/* Bir stringin uzunlugunu bulan fonksiyon */
int myLen(char * arr)
{
	int i;
	for (i=0; arr[i] != '\0'; i++);
	
	return i;
}

































