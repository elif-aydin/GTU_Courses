/* Gerekli kutuphaneler */

#include <dirent.h>     /* opendir closedir */
#include <stdio.h>
#include <stdlib.h>     /* Malloc ve exit icin */
#include <string.h>     /* Strlen icin */
#include <unistd.h>     /* fork    */
#include <sys/wait.h>   /* wait    */
#include <sys/types.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <time.h>

#define LOG_FILE "log.txt"
#define Lines "line.log"
#define Files "file.log"
#define Dirs  "dir.log"
#define Threads  "thread.log"


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
/*void listFromFile(const char * inputFileName, const char * target);*/
void *listFromFile(void * info);


/**
 * Bu fonksiyon directory içinde recursive olarak directory arar.
 * @param inputFileName icinde arama yapacagimiz dosya
 * @param dosya icinde arayacagimiz kelime
 * @return void
*/
void listdirFile(const char * inputFileName, const char * target);

void INThandler(int);

void printResult();


int numOfDir;
int numOfFile;
int numOfLine;
int numOfThread;
int numofConThread;
char line[64];
pthread_t thread_id;
pthread_mutex_t lock;
clock_t begin;
clock_t end;
double elapsedTime;
int totalChar = 0;


struct info 
{
    char inputFileName[512];
    char target[512];
};

/******************
*  START OF MAIN  *
*******************/  
int main(int argc, char * argv [])
{
    char * target;
    char * fileName;
    char * exeCommand;
    char tempChar;
    FILE *filePointer, *fp, *file_pointer;
    FILE *fp1, *fp2, *fp3, *fp4;

    signal(SIGINT, INThandler);

    if(argc != 3 || strcmp("./grepTh", argv[0]) != 0) /* USAGE */
    {
        printf("\n\n------------------USAGE-------------------\n");
        printf("You need enter for executable name ->> grepTh\n");
        printf("You need enter the string who you want search in file\n");
        printf("You need enter the file name\n\n");
        printf("-----Sample----");
        printf("\n./grepTh target folderName\n\n");

        exit (1);
    }

    target = argv[1];
    fileName = argv[2];
    exeCommand = argv[0];

    begin = clock();

    filePointer = fopen(LOG_FILE, "r");

    if (filePointer != NULL)
    {
        remove(LOG_FILE);     
        fclose(filePointer);
    }

    numOfDir = 0;
    numOfFile = 0;
    numOfLine = 0;
    numOfThread = 0;
    numofConThread = 0;

    fp = fopen(Files, "w"); /* Toplam file sayisi icin acariz */
    fclose(fp);
    fp = fopen(Lines, "w"); /* Toplam satir sayisi icin acariz */
    fclose(fp);
    fp = fopen(Dirs, "w"); /* Toplam dir sayisi icin acariz */
    fclose(fp);
    fp = fopen(Threads, "w"); /* Toplam thread sayisi icin acariz */
    fclose(fp);
    
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n Mutex init failed\n");
        return 1;
    }
    
    listdirFile(fileName, target);  
    pthread_mutex_destroy(&lock);

    end = clock();
    elapsedTime = (double)(end - begin) / CLOCKS_PER_SEC*1000;

    fp = fopen(LOG_FILE, "r"); /* Toplam karakter sayisi icin acariz */
    while(fscanf(fp, "%c", &tempChar) != EOF)
    {   
        if(tempChar == '\n')
            totalChar ++;
    } 
    fclose(fp);

    file_pointer = fopen(LOG_FILE, "a");
    fprintf(file_pointer,"\n %d %s were found in total.",totalChar,target);

    printResult();
    printf("Exiting normal\n");

  
    fp1 = fopen(Lines, "r");
    fp2 = fopen(Files, "r");
    fp3 = fopen(Dirs, "r");
    fp4 = fopen(Threads, "r");


    if (fp1 != NULL && fp2 != NULL && fp3 != NULL && fp4 != NULL)
    {
        remove(Lines);
        remove(Files);        
        remove(Dirs);        
        remove(Threads);        
        
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
        fclose(fp4);
    }

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
    int i,j, tCount;
    struct info *data = malloc(sizeof(struct info));
    pid_t pidChild; /* pid_t to use fork function */
    FILE *fpDirs, *fpFiles;

    tCount = 0;
    fpDirs = fopen(Dirs,"a");
    fpFiles = fopen(Files,"a");
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
                
                dp2 = opendir (newDir);
                if (dp2 != NULL)
                { 
                    pidChild = fork();
                    if(pidChild == 0) 
                    {
                        listdirFile(newDir,target);
                        closedir(dp2);
                        closedir(dp);
                        fprintf(fpDirs,"1\n");
                        fclose(fpDirs);
                        fclose(fpFiles);
                        free(data);
                        exit (0);
                    }
                    else 
                    {
                        pidChild = waitpid(pidChild, NULL, 0);
                    }
                    closedir(dp2);
                }
                else
                {  
                    strcpy(data->inputFileName, newDir);
                    strcpy(data->target, target);
                    pthread_create(&thread_id, NULL, listFromFile, data);
                    pthread_join(thread_id, NULL);  
                    tCount ++;
                }
            }
        } 

        printf("Number of cascade threads created for %5ld: %d\n", (long) getpid(), tCount);
        closedir(dp);            
    }
    else
    {
    	perror ("Couldn't open the directory");
        free(data);
        fprintf(fpFiles,"%d\n", tCount);
        fclose(fpDirs);
        fclose(fpFiles);
        exit(1);
    }

	free(data);
    fprintf(fpFiles,"%d\n", tCount);
    fclose(fpDirs);
    fclose(fpFiles);
}


void *listFromFile(void * info)
{
    
    FILE* filePointer, *fpLines, *tempFile ;
    char target[512];
    char inputFileName[512];

    char * charArray; /* Dosyayi tutacagimiz array */
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
    struct info *param = (struct info*) info;    
    pthread_mutex_lock(&lock);
    pid_t tid = syscall(SYS_gettid);   

    tempFile = fopen(LOG_FILE, "a");

    /* Arrayimiz icin fileSize kadar yer aliyoruz */
   
    strcpy(target, param->target);
    strcpy(inputFileName, param->inputFileName);
    
    fpLines=fopen(Lines,"a");
    if(tempFile == NULL)
    {
        printf("\nFile could not open !\n");
        exit(1);
    }

    /* Dosyanin boyunu bulduk */
    fileSize = numberOfFileSize(inputFileName);

    charArray = (char*) malloc(fileSize * sizeof(char));

    /* Dosyayi array e atmak uzere acariz. */
    filePointer = fopen(inputFileName, "r");
    if(filePointer == NULL)
    {
        printf("\nFile could not open !\n");
        exit(1);
    }

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

                fprintf(tempFile, "PID: %5ld - TID: %5ld   %s: [%d, %d] %s first character is found.\n", (long) getpid(), ((long)tid), &inputFileName[temp+1], rowCounter,colCounter,target);
            }
       }
        colCounter ++;
        
        if (charArray[fileIndex] == '\n') /* Dondugunde kaldigi satir saiyisi*/
        {
            rowCounter++;
            colCounter = 1;
            numOfLine++;
        }

        fileIndex ++;
        tempIndex = fileIndex;
    }
    fprintf(fpLines,"%d\n",numOfLine);
    fclose(fpLines);
    free(charArray);
    fclose(tempFile);
    pthread_mutex_unlock(&lock);
    return 0;
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


void  INThandler(int sig)
{
    printResult();
    printf("Exiting Ctrl-C \n");
    exit(0); 
}


void printResult()
{
    FILE *fp;
    int max;

    max = 0;
    fp = fopen(Files, "r"); /* Toplam file sayisi icin acariz */
    while (fgets(line, sizeof(line), fp)) 
    {
        if(atoi(line)> max)
            max = atoi(line);
        
        numOfFile += atoi(line);
    }
    fclose(fp);

    fp = fopen(Dirs, "r"); /* Toplam dir sayisi icin acariz */
    while(fgets(line, sizeof(line), fp)) 
    {
        numOfDir++;
    }
    fclose(fp);
    
    fp = fopen(Lines, "r"); /* Toplam line sayisi icin acariz */
    while (fgets(line, sizeof(line), fp)) 
    {
        numOfLine+=atoi(line);
    }
    fclose(fp);

    printf("Total number of strings found :           %d\n", totalChar);
    printf("Number of directories searched:           %d\n", numOfDir+1);
    printf("Number of files searched:                 %d\n", numOfFile);
    printf("Number of lines searched:                 %d\n", numOfLine);
    printf("Number of search threads created:         %d\n", numOfThread+numOfFile);
    printf("Max # of threads running concurrently:    %d\n", max);
    printf("Total run time, in milliseconds.          %lf\n", elapsedTime);   
}