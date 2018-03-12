/* Gerekli kutuphaneler */
#include <stdio.h>
#include <stdlib.h> /* Malloc ve exit icin */
#include <string.h> /* Strlen icin */

/* *
 * Bu fonksiyon once dosyayi acar dosyayi sonuna kadar okur ve
 * dosyadaki toplam karakter sayisini bulup return eder.
 * @param fileName karakter sayisini bulacagimiz file
 * @return characterCount dosyadaki karakter sayisi
 */
int numberOfFileSize(const char * fileName);

/**
 * Bu fonksiyon parametre olarak aldigi string i yine parametre olarak aldigi
 * file icinde arar ve buldugu her bir kelimenin basladigi yeri ekrana basar.
 * Toplamda kac kelime buldugu return eder. 
 * @param inputFileName icinde arama yapacagimiz dosya
 * @param dosya icinde arayacagimiz kelime
 * @return verilen kelimenin verilen dosyada kac defa gectigi
*/
int listFromFile(const char * inputFileName, const char * target);


/*
	START OF MAIN
*/	
int main(int argc, char * argv [])
{
	int total = 0;
	char * target = argv[1];
	char * file = argv[2];
	char * exeCommand = argv[0];
	int value = strcmp("./list", exeCommand);
	
	if(argc != 3 || value != 0) /* USAGE */
	{
		printf("\n\n------------------USAGE-------------------\n");
		printf("You need enter for executable name ->> list\n");
		printf("You need enter the string who you want search in file\n");
		printf("You need enter the file name\n\n");

		exit (1);
	}
	else 
	{
		total = listFromFile(file,target);
		printf("\n%d adet %s bulundu.\n",total,target);
	}
	return 0;
}

/*
	END OF MAIN
*/

int listFromFile(const char * inputFileName, const char * target)
{
	FILE* filePointer ;

	char* charArray; /* Dosyayi tutacagimiz array */

	int fileSize;
	int fileIndex;
	int colCounter;
	int rowCounter;
	/*int tempRow;*/
	int targetLength;
	int tempIndex;
	int i;
	int findMatching;
	int notMatch;
	char charTemp;


	/* Dosyanin boyunu bulduk */
	fileSize = numberOfFileSize(inputFileName);

	/* Dosyayi array e atmak uzere acariz. */
	filePointer = fopen(inputFileName, "r");
	if(filePointer == NULL)
	{
		printf("\nFile could not open !\n");
		exit(1);
	}

	/* Arrayimiz icin fileSize kadar yer aliyoruz */
	charArray = (char*) malloc(fileSize * sizeof(char));

	/* Dosyayi char arrayimize atariz */
	for(i = 0; i < fileSize; i++)
	{
		fscanf(filePointer, "%c", &charTemp);
		charArray[i] = charTemp;
	}

	fclose(filePointer); /* Dosyayi kapatiriz. */

	/* Degiskenlerin initialize edilmesi */
    tempIndex = 0;
    fileIndex = 0; /* Tum array i dolasan index */
    rowCounter = 1;
    colCounter = 1;
    /*tempRow = 1; Satiri saklar */
    findMatching = 0;
    targetLength = strlen(target);

    while(fileIndex < fileSize) /* Tum array i dolasiyoruz. */
    {
		notMatch = 0;
		i = 0;
		if (charArray[tempIndex] == target[i]) 
		{
			while((i < targetLength) && (tempIndex < fileSize)&& (notMatch == 0)) /* Array sinir kontrolu */
			{
				if(charArray[tempIndex] == ' ' || charArray[tempIndex] == '\t' || charArray[tempIndex] == '\n')
					tempIndex ++;

				else if(charArray[tempIndex] != target[i])
					notMatch = 1; /*eslesme olmazsa*/

				else
	            {
					i ++;
					tempIndex ++;
				}
			}
	        if ((notMatch == 0) && (i == targetLength))
	        {
	            findMatching ++;
	            printf("\n[%d, %d] konumunda ilk karakter bulundu.\n",rowCounter,colCounter);
	        }
	   }

		colCounter ++;
		
		if (charArray[fileIndex] == '\n') /* Dondugunde kaldigi satir saiyisi*/
		{
			rowCounter++;
			colCounter = 1;
		}

		fileIndex ++;
		/*rowCounter = tempRow;*/
		tempIndex = fileIndex;
	}

	free(charArray);
	return findMatching;
}


int numberOfFileSize(const char * fileName)
{
	FILE* filePointer;
    
    char tempChar;
    int characterCount; /* Dosyanın size ini tutariz */

    filePointer = fopen(fileName, "r"); /* Dosyayi okumak icin aciyoruz */
    
    if(filePointer == NULL) /* Dosya acilma hatasi olusursa */
    {
            printf("File could not open \n");
            exit(1);
    }

    characterCount = 0;
    /* Dosyanin sonuna kadar okuruz ve size buluruz. */
    while(fscanf(filePointer, "%c", &tempChar) != EOF)
    {
    	characterCount ++;
    }

    fclose(filePointer); /* Dosyayi kapatiyoruz */

    return characterCount;
}