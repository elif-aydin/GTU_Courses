/* Gerekli kutuphaneler */
#include <dirent.h>     /* opendir closedir */
#include <stdio.h>
#include <stdlib.h>     /* Malloc ve exit icin */
#include <string.h>     /* Strlen icin */
#include <unistd.h>     /* fork    */
#include <pthread.h>
#include <time.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/wait.h>   /* wait    */
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/resource.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 

#define LOG_FILE "log.txt"
#define MAXSIZE 128
#define SHM_BLOCK_SIZE 1024


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

void putEof();

void printResult();

/* 
 *ınitialize memory variables
*/
void initializeMem();

/* 
 *Update shared memory variables 
*/
void updateMem(int position, int addValue);



int numOfThread;
int numOfDir = 0;
int numOfFile = 0;
int numOfLine = 0;
int numofConThread;
char line[64];
pthread_t thread_id;
pthread_mutex_t lock, memLock;
clock_t begin, end;

double elapsedTime;
int totalChar = 0;
int maxThread = 0;
key_t file_key = 11111;
key_t dir_key  = 22222;
key_t line_key = 33333;
int file_id, dir_id, line_id;
size_t buflen;
key_t shm_key = 11111;
int shm_id;
char* shmaddr;


struct info 
{
    char inputFileName[512];
    char target[512];
};

struct msgbuf
{
    int    mtype;
    char   mtext[MAXSIZE];
};
struct msgbuf msgBuffer;


int findNumberOfFiles(char * folderName)
{
    int fileCount = 0;
    DIR * dirp;
    struct dirent * entry;

    dirp = opendir(folderName); 
    while ((entry = readdir(dirp)) != NULL) 
    {
        if (entry->d_type == DT_REG) 
        {
             fileCount++;
        }
    }
    closedir(dirp);

    return fileCount;
}


/******************
*  START OF MAIN  *
*******************/  
int main(int argc, char * argv [])
{
    char * target;
    char * fileName;
    int msgflg = IPC_CREAT | 0666;
    char tempChar;
    FILE *filePointer, *fp, *file_pointer;

    struct rlimit limit;
    limit.rlim_cur = 1000000000;
    limit.rlim_max = 1000000000;

    setrlimit(RLIMIT_STACK,&limit);

    signal(SIGINT, INThandler);

    if(argc != 3 || strcmp("./grepSh", argv[0]) != 0) /* USAGE */
    {
        printf("\n\n------------------USAGE-------------------\n");
        printf("You need enter for executable name ->> grepTh\n");
        printf("You need enter the string who you want search in file\n");
        printf("You need enter the file name\n\n");
        printf("-----Sample----");
        printf("\n./grepSh target folderName\n\n");

        exit (1);
    }

    target = argv[1];
    fileName = argv[2];

    begin = clock();

    filePointer = fopen(LOG_FILE, "r");

    if (filePointer != NULL)
    {
        remove(LOG_FILE);     
        fclose(filePointer);
    }

    /* Create message queues. */
    file_id = msgget(file_key, msgflg );
    dir_id  = msgget(dir_key , msgflg );
    line_id = msgget(line_key, msgflg );

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n Mutex init failed\n");
        return 1;
    }
    if (pthread_mutex_init(&memLock, NULL) != 0)
    {
        printf("\n Memory Mutex init failed\n");
        return 1;
    } 

    listdirFile(fileName, target);  
    pthread_mutex_destroy(&lock);

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
    pthread_mutex_destroy(&memLock);
    fclose(file_pointer);

    /* Release allocated queue memory */    
    msgctl(dir_id, IPC_RMID, NULL);
    msgctl(file_id, IPC_RMID, NULL);
    msgctl(line_id, IPC_RMID, NULL);
    return 0;
}
/*
    END OF MAIN
*/

void listdirFile(const char * inputFileName, const char * target)
{
    DIR *dp, *dp2;
    struct dirent *pDirent;
    char  newDir[256] = "\0";
    int i, j, tCount, fileCount;
    struct info * data = malloc(sizeof(struct info));
    pid_t pidChild; /* pid_t to use fork function */

    tCount = 0;

    dp = opendir(inputFileName);
    if(dp != NULL)
    {
        while((pDirent = readdir(dp)))
        {
            if((strcmp(pDirent->d_name,".") != 0) && (strcmp(pDirent->d_name, "..") != 0) && pDirent->d_name[strlen(pDirent->d_name) - 1] != '~')
            {
                for(i = 0; i < strlen(inputFileName); i++)
                    newDir[i] = inputFileName[i];

                newDir[i] = '/';

                for(j = 0; j < strlen(pDirent->d_name); j++)
                    newDir[i+j+1] = pDirent->d_name[j];
                
                newDir[i+j+1] = '\0';
                
                dp2 = opendir (newDir);
                if(dp2 != NULL)
                { 
                    pidChild = fork();
                    if(pidChild == 0) 
                    {
                        fileCount = findNumberOfFiles(newDir);
                        if (fileCount != 0)
                        {
                            printf("Shared memory for file %s: %d * %d = %d\n", pDirent->d_name, fileCount, SHM_BLOCK_SIZE, fileCount * SHM_BLOCK_SIZE);
                        }
                        else
                        {
                            printf("Shared memory for file %s: 0\n", pDirent->d_name);
                        }

                        listdirFile(newDir, target);
                        closedir(dp2);
                        closedir(dp);
                        msgBuffer.mtype = 1;
                        sprintf(msgBuffer.mtext, "1");
                        buflen = strlen(msgBuffer.mtext) + 1 ;          
                        msgsnd(dir_id, &msgBuffer, buflen, 0);  /*Increase number of directory variable*/
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
        msgBuffer.mtype = 1;
        sprintf(msgBuffer.mtext, "%d", tCount);
        buflen = strlen(msgBuffer.mtext) + 1 ;          
        msgsnd(file_id, &msgBuffer, buflen, 0);

        if (maxThread < tCount)
            maxThread = tCount;
        
        exit(1);
    }

    free(data);
    msgBuffer.mtype = 1;
    sprintf(msgBuffer.mtext,"%d", tCount);
    buflen = strlen(msgBuffer.mtext) + 1 ;          
    msgsnd(file_id, &msgBuffer, buflen, 0); /*Update number of files*/
    if (maxThread<tCount)
            maxThread=tCount;
}


void *listFromFile(void * info)
{   
    FILE* filePointer, *tempFile ;
    char target[512];
    char inputFileName[512];

    char * charArray; /* Dosyayi tutacagimiz array */
    int fileSize;
    int fileIndex;
    int colCounter;
    int rowCounter;
    int targetLength;
    int tempIndex;
    int i, k;
    int notMatch;
    char charTemp;
    int temp;
    struct info *param = (struct info*) info;    
    pid_t tid = syscall(SYS_gettid);   

    pthread_mutex_lock(&lock);
    tempFile = fopen(LOG_FILE, "a");

    /* Arrayimiz icin fileSize kadar yer aliyoruz */
   
    strcpy(target, param->target);
    strcpy(inputFileName, param->inputFileName);
    
    if(tempFile == NULL)
    {
        perror("\nFile could not open !\n");
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

    msgBuffer.mtype = 1;
    sprintf(msgBuffer.mtext, "%d", numOfLine);
    buflen = strlen(msgBuffer.mtext) +1 ;          
    msgsnd(line_id, &msgBuffer, buflen, 0); /*Update number of lines*/
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
    msgctl(dir_id, IPC_RMID, NULL);
    msgctl(file_id, IPC_RMID, NULL);
    msgctl(line_id, IPC_RMID, NULL);
    exit(0); 
}


void printResult()
{
    numOfLine = 0;
    numOfFile = 0;
    numOfDir = 0;
    putEof(); /*Put end of message marker for each queue*/
    while (msgrcv(file_id, &msgBuffer, MAXSIZE, 0, 0) >= 0) 
    {
        if (atoi(msgBuffer.mtext) == 123456789)
            break;
        numOfFile += atoi(msgBuffer.mtext);
    }
 
    while(msgrcv(dir_id, &msgBuffer, MAXSIZE, 0, 0) >= 0) 
    {
        if (atoi(msgBuffer.mtext) == 123456789)
            break;
        numOfDir++;
    }
    
    while(msgrcv(line_id, &msgBuffer, MAXSIZE, 0, 0) >= 0) 
    {   
        if (atoi(msgBuffer.mtext) == 123456789)
            break;
        numOfLine += atoi(msgBuffer.mtext);
    }
    end = clock();
    elapsedTime = (double)(end - begin) / CLOCKS_PER_SEC * 1000;

    printf("Total number of strings found :           %d\n", totalChar);
    printf("Number of directories searched:           %d\n", numOfDir+1);
    printf("Number of files searched:                 %d\n", numOfFile);
    printf("Number of lines searched:                 %d\n", numOfLine);
    printf("Number of search threads created:         %d\n", numOfFile);
    printf("Max # of threads running concurrently:    %d\n", maxThread);
    printf("Shared memory count                       %d\n", numOfDir + 1);
    printf("Total run time, in milliseconds.          %.3f\n", elapsedTime);   
}

/*Put the End of message to each queue*/
void putEof()
{
    msgBuffer.mtype = 1;
    sprintf(msgBuffer.mtext, "123456789");
    buflen = strlen(msgBuffer.mtext) + 1 ;          
    msgsnd(line_id, &msgBuffer, buflen, IPC_NOWAIT);
    msgsnd(dir_id, &msgBuffer, buflen, IPC_NOWAIT);
    msgsnd(file_id, &msgBuffer, buflen, IPC_NOWAIT);
}

/* Initialize shared memory variables */
void initializeMem()
{
  char* ptr;
  int next[3];

  /* Allocate a shared memory segment. */
  shm_id = shmget (shm_key, SHM_BLOCK_SIZE, IPC_CREAT | S_IRUSR | S_IWUSR);

  /* Attach the shared memory segment. */
  shmaddr = (char*) shmat (shm_id, 0, 0);

  /* Initialize variables. */
  ptr = shmaddr + sizeof (next);
  next[0] = sprintf (ptr, "%d",0) + 1; /*First variable is file number*/
  ptr += next[0];
  next[1] = sprintf (ptr, "%d",0) + 1; /*Second variable is directory  number*/
  ptr += next[1];
  next[2] = sprintf (ptr, "%d",0) + 1; /*Third  variable is line  number*/
  ptr += next[2];
  sprintf (ptr, "%d",0);  /*Fourth variable is thread number*/
  memcpy(shmaddr, &next, sizeof (next));
}


void updateMem(int position, int addValue)
{
  char* ptr;
  char* shared_memory[4];
  int *p;
  int next[3], file, dir, line, thread;
  
  /* Start to read data. */
  p = (int *)shmaddr;
  ptr = shmaddr + sizeof (int) * 3;
  shared_memory[0] = ptr;
  ptr += *p++;
  shared_memory[1] = ptr;
  ptr += *p++;
  shared_memory[2] = ptr;
  ptr += *p;
  shared_memory[3] = ptr;
  file = atoi(shared_memory[0]);
  dir  = atoi(shared_memory[1]);
  line = atoi(shared_memory[2]);
  thread = atoi(shared_memory[3]);
  if      (position==0) file  +=addValue;
  else if (position==1) dir   +=addValue;
  else if (position==2) line  +=addValue;
  else                  thread+=addValue;
  
  /* Start to update shared memory variables. */
  ptr = shmaddr + sizeof (next);
  next[0] = sprintf (ptr, "%d",file) + 1;
  ptr += next[0];
  next[1] = sprintf (ptr, "%d",dir) + 1;
  ptr += next[1];
  next[2] = sprintf (ptr, "%d",line) + 1;
  ptr += next[2];
  sprintf (ptr, "%d",thread);
  memcpy(shmaddr, &next, sizeof (next));
}