/* Gerekli kutuphaneler */

#include <dirent.h>     /* opendir closedir */
#include <stdio.h>
#include <stdlib.h>     /* Malloc ve exit icin */
#include <string.h>     /* Strlen icin */
#include <unistd.h>     /* fork    */
#include <sys/wait.h>   /* wait    */


#define LOG_FILE "log.log"

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
 * Toplamda kac kelime buldugu return eder. cl
 * @param inputFileName icinde arama yapacagimiz dosya
 * @param dosya icinde arayacagimiz kelime
 * @return void
*/
void listFromFile(const char * inputFileName, const char * target);


/**
 * Bu fonksiyon directory içinde recursive olarak directory arar.
 * @param inputFileName icinde arama yapacagimiz dosya
 * @param dosya icinde arayacagimiz kelime
 * @return void
*/
void listdirFile(const char * inputFileName, const char * target);


/******************
*   START OF MAIN *
*******************/  
int main(int argc, char * argv [])
{
    char * target = argv[1];
    char * fileName = argv[2];
    char * exeCommand = argv[0];
    int  totalChar = 0;
    char tempChar;

    int value = strcmp("./listdir", exeCommand);

    if(argc != 3 || value != 0) /* USAGE */
    {
        printf("\n\n------------------USAGE-------------------\n");
        printf("You need enter for executable name ->> listdir\n");
        printf("You need enter the string who you want search in file\n");
        printf("You need enter the file name\n\n");
        printf("-----Sample----");
        printf("\n./listdir target folderName\n\n");

        exit (1);
    }

    FILE * filePointer = fopen(LOG_FILE, "r");
    if (filePointer != NULL)
    {
        remove(LOG_FILE);        
        fclose(filePointer);
    }

    listdirFile(fileName,target);  

    FILE * fp = fopen(LOG_FILE, "r"); /* Toplam karakter sayisi icin acariz */

    while(fscanf(fp, "%c", &tempChar) != EOF)
    {
        if(tempChar == '\n')
            totalChar ++;
    }

    fclose(fp);

    FILE * file_pointer = fopen(LOG_FILE, "a");
    fprintf(file_pointer,"\n %d %s were found in total.",totalChar,target);

    fclose(file_pointer);
    return 0;
}
/*
    END OF MAIN
*/

void listdirFile(const char * inputFileName, const char * target)
{
    DIR *dp,*dp2;
    struct dirent *pDirent;
    char  newDir[256]="\0";
    int i,j;
    pid_t pidChild; /* pid_t to use fork function */

    dp = opendir (inputFileName);
    if (dp != NULL)
    {
        while ((pDirent = readdir (dp)))
        {
            if ((strcmp(pDirent->d_name,".") != 0) && (strcmp(pDirent->d_name, "..") != 0) && pDirent->d_name[strlen(pDirent->d_name) - 1] != '~')
            {
                for (i = 0; i < strlen(inputFileName); i++)
                    newDir[i] = inputFileName[i];

                newDir[i] = '/';

                for (j = 0; j < strlen(pDirent->d_name); j++)
                    newDir[i+j+1] = pDirent->d_name[j];
                
                newDir[i+j+1] = '\0';

                pidChild = fork();
                if(pidChild >= 0) /* Fork is succes */
                {
                    if(pidChild == 0) /* Child Process */
                    {
                        dp2 = opendir (newDir);
                
                        if (dp2 != NULL)
                        {
                            listdirFile(newDir,target);
                        }
                
                        else
                        {
                            listFromFile(newDir,target);
                        }

                        closedir (dp2);
                        
                        exit(0);
                    }
 
                    else /* parent part. should wait all childs  */
                    {   
                        pidChild = waitpid(pidChild, NULL, 0);
                    }
                }
                else
                {
                    perror("Fork is not okay\n");
                    exit(0);
                }
            }
        } 
           
        closedir (dp);
    }

    else
        perror ("Couldn't open the directory");
}


void listFromFile(const char * inputFileName, const char * target)
{
    FILE* filePointer ;

    char* charArray; /* Dosyayi tutacagimiz array */

    int fileSize;
    int fileIndex;
    int colCounter;
    int rowCounter;
    int targetLength;
    int tempIndex;
    int i,k;
    int notMatch;
    char charTemp;
    int temp;

    FILE * tempFile = fopen(LOG_FILE, "a");
    if(tempFile == NULL)
    {
        printf("\nFile could not open !\n");
        exit(1);
    }

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
                for(k = 0; k < strlen(inputFileName); k++)
                {
                    if(inputFileName[k] == '/')
                        temp = k;
                }

                fprintf(tempFile, "%s: [%d, %d] %s first character is found.\n", &inputFileName[temp+1], rowCounter,colCounter,target);
            }
       }

        colCounter ++;
        
        if (charArray[fileIndex] == '\n') /* Dondugunde kaldigi satir saiyisi*/
        {
            rowCounter++;
            colCounter = 1;
        }

        fileIndex ++;
        tempIndex = fileIndex;
    }

    free(charArray);
    fclose(tempFile);
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