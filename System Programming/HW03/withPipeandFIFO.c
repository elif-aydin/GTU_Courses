#include "withPipeandFIFO.h" 


/*Seach specified directory*/
int searchForDirectory(const char *string, char *dirPath) 
{
    pid_t child;
    int tempChild = 0; 
    int totalChild = 0; 
    int tempDirCount = 0;
    int totalDirCount = 0;
    int i = 0;
    int totalFound = 0;
    int status = 0;
    int fifoWrite = 0;
    int fifoRead = 0;
    int target[2];
    int dirCount = 0;
    int fileCount = 0;
    int temp = 0;
    int index = 0;
    char * afterSlash = NULL;
    DIR *dirPointer = NULL;
    struct dirent *direntPtr = NULL;
    char subDirPath[BUFFER] ; 
    /*subDirPath[BUFFER-1]='\0';*/
    char fifoName[MAX_PATH];
    /*fifoName[256] = NULL;*/
    /*fifoName[MAX_PATH-1] = '\0';*/
    char fifoNameArray[MAX_PATH][MAX_PATH] = {{0}};
    

    for (i = 0; i < MAX_PATH; ++i)
    	fifoNameArray[i][MAX_PATH-1]='\0';

    i = 0;

    numOfObjects(dirPath, &dirCount, &fileCount);
    
	/* Fifo olusturulur */
    createFifos(dirPath, fifoNameArray);

    /* Pipe olusturulur */
    if (fileCount > 0) 
    {
        if (pipe(target) == -1) 
        {
            perror("\nPipe failed\n");
            exit(EXIT_FAILURE);
        }

        write(target[1], &temp, sizeof (temp));
    }


	dirPointer = opendir(dirPath);
	if (dirPointer == NULL)
		fprintf(stderr, "\nDirectory could not open\n");

    
    else 
    {
        while ((direntPtr = readdir(dirPointer)) != NULL) 
            if (strcmp(direntPtr->d_name, ".") != 0 && strcmp(direntPtr->d_name, "..") != 0 && direntPtr->d_name[strlen(direntPtr->d_name) - 1] != '~') 
            {
                /* Sub directory name ( subDirPath ) */
                sprintf(subDirPath, "%s/%s", dirPath, direntPtr->d_name);
                if (isDirectory(subDirPath) != 0) 
                { 
                	child = fork(); /* Directory */
                    if (child == 0) 
                    {
                        searchForDirectory(string, subDirPath);
                        closedir(dirPointer);
                        exit(EXIT_SUCCESS);
                    }
                }

                else if (isDirectory(subDirPath) == 0) 
                { 
                    child = fork(); /* File */
                    if (child == 0) 
                    {
                        tempChild = listFromFile(subDirPath, LOG_FILE, string, target);
                        read(target[0], &totalChild, sizeof (totalChild));

                        totalChild = totalChild + tempChild;
                        write(target[1], &totalChild, sizeof (totalChild)); /* Child sonucunu kaydeder */

			            closedir(dirPointer);
                        exit(EXIT_SUCCESS);
                    }
				}
            }

        closedir(dirPointer); /* Directory kapatilir */
    }

    /* Directory sonuclarini okur */
    for (i = 0; i < dirCount; ++i) 
    {
        sprintf(fifoName, "%s", fifoNameArray[i]);
        if ((fifoRead = open(fifoName, O_RDONLY)) != -1) 
        {
            read(fifoRead, &tempDirCount, sizeof (tempDirCount));
            close(fifoRead);
            unlink(fifoName);
            totalDirCount += tempDirCount;
        }
    }

    /* Tum cocuklari bekler */
    while (wait(&status) != -1) 
        if (status != EXIT_SUCCESS) 
            fprintf(stderr, "Error in fork procces %d\n", status);


    if (fileCount > 0)  /* Pipe i okuruz */
        read(target[0], &tempDirCount, sizeof (tempDirCount));

    totalFound = tempDirCount + totalDirCount;

    if (getpid() != pidFlag) 
    {
        index = findLastSlash(dirPath, strlen(dirPath));
        afterSlash = &dirPath[index+1];

        sprintf(fifoName, "%d-%s", getppid(), afterSlash);
        fifoWrite = open(fifoName, O_WRONLY);
        write(fifoWrite, &totalFound, sizeof (totalFound));
        close(fifoWrite);
    }
    return totalFound;
}

void numOfObjects(const char *dirPath, int *dirCount, int *fileCount) 
{
	int tempDir = 0;
    int tempFile = 0;
    struct dirent *direntPtr;
    DIR *dirPtr;
    char subDirPath[BUFFER];
    subDirPath[BUFFER-1] = '\0';


    dirPtr = opendir(dirPath);

    if (dirPtr == NULL) 
        fprintf(stderr,"\n Directory could not open \n"); 
    
    else 
    {
        while ((direntPtr = readdir(dirPtr)) != NULL) 
            if (strcmp(direntPtr->d_name, "..") != 0 && strcmp(direntPtr->d_name, ".") != 0) 
            {
                sprintf(subDirPath, "%s/%s", dirPath, direntPtr->d_name);
                if (isDirectory(subDirPath) != 0) 
                {
                    tempDir ++; /* Dir sayisi artirdik */
                    numOfObjects(subDirPath, &tempDir, &tempFile);
                } 

                else if (direntPtr->d_name[strlen(direntPtr->d_name) - 1] != '~') 
                    tempFile ++; /* File sayisi artirdik */
            }
        
        closedir(dirPtr);
    }
    *dirCount += tempDir;
    *fileCount += tempFile;
}

/* Bu fonksiyon her bir directory icin fifo olusturur.*/
void createFifos(const char *dirPath, char charArray[MAX_DIR][MAX_PATH]) 
{
    DIR *dirPointer;
    struct dirent *direntPtr;
    char subDirPath[BUFFER];
    char fifoName[256];
    int i;
    int j;
    subDirPath[BUFFER-1]='\0';
    fifoName[255]='\0';
    i = 0;
    j = 0;

    dirPointer = opendir(dirPath);

    if (dirPointer == NULL) 
        fprintf(stderr, "\nDirectory could not open\n");

    else 
    {
        while ((direntPtr = readdir(dirPointer)) != NULL) 
        {
            if (strcmp(direntPtr->d_name, ".") != 0 && strcmp(direntPtr->d_name, "..") != 0) 
            {
                sprintf(subDirPath, "%s/%s", dirPath, direntPtr->d_name);

                if (isDirectory(subDirPath) != 0) 
                {
                    sprintf(fifoName, "%d-%s", getpid(), direntPtr->d_name);
                    
                    for(j = 0; j < strlen(fifoName); j++)
                        charArray[i][j] = fifoName[j];

                    charArray[i][j] = '\0';       
                    i++;

                    if (mkfifo(fifoName, 0600) == -1) 
                    {
                        perror("Failed to create FIFO...");
                        closedir(dirPointer);
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
        closedir(dirPointer);
    }
}

int listFromFile(const char *inputFileName, const char *outputFileName, const char *target, int pipeArray[2]) 
{
    FILE* inputFilePtr;
    FILE* outputFilePtr;

    char* charArray; /* Dosyayi tutacagimiz array */
    int fileSize;
    int fileIndex;
    int notMatch;
    int i;
    int temp;
    int targetLength;
    int tempIndex;
    int k;
    char charTemp;
    int foundWord; /* İstenilen kelimenin gecme sayisi */
    int rowCounter; 
    int colCounter;

    targetLength = strlen(target);

    /* Dosyanin boyunu bulduk */
    fileSize = numberOfFileSize(inputFileName);
    if (fileSize == -1) 
    {
        return 0;
    }

    /* Dosyayi array e atmak uzere acariz */
    inputFilePtr = fopen(inputFileName, "r");
    if (inputFilePtr == NULL) 
    {
        perror("\nFile could not open \n");
        exit(1);
    }

    /* Dynamic allocation */
    charArray = (char*) malloc((fileSize+1) * sizeof (char));

    /* Dosyayi char arrayimize atariz */
    for(i = 0; i < fileSize; i++)
    {
        fscanf(inputFilePtr, "%c", &charTemp);
        charArray[i] = charTemp;
    }
    
    /* Sonuna null terminator ekledik */
    charArray[i] = '\0';
    fclose(inputFilePtr);

    /* log file in acilmasi */
    outputFilePtr = fopen(LOG_FILE, "a+");
    if (outputFilePtr == NULL) 
    {
        perror("\nFile could not open \n");
        exit(1);
    }

    /* Degiskenlerin initialize edilmesi */
    i = 0;
    fileIndex=0;
    tempIndex = 0;
    fileIndex = 0; /* Tum array i dolasan index */
    rowCounter = 1;
    colCounter = 1;
    k = 0;
    foundWord = 0;
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
                    notMatch = 1; /* In any unmatch  set as notMatch */
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

                foundWord++;
                fprintf(outputFilePtr, "%s: [%d, %d] %s first character is found.\n", &inputFileName[temp+1], rowCounter,colCounter,target);
            }
       }

        colCounter ++;

        if (charArray[fileIndex] == '\n') /* Dondugunde kaldigi satir sayisi */
        {
            rowCounter++;
            colCounter = 1;
        }

        fileIndex ++;
        tempIndex = fileIndex;
    }
    
    /* Free dynamic memory */
    free(charArray);
    fclose(outputFilePtr);
    return foundWord;
}

int numberOfFileSize(const char *fileName) 
{
    FILE* filePointer;
    int characterCount; /* Dosyanin size ini tutariz */
    char tempChar;
    
    filePointer = fopen(fileName, "r"); /* Dosyayi okumak icin aciyoruz */

    if (filePointer == NULL) /* Dosya acilma hatasi olusursa */
    {
        perror("File could not open \n");
        exit(1);
    }

    characterCount = 0;
    /* Dosyanin sonuna kadar okuruz ve size buluruz */
    while (fscanf(filePointer, "%c", &tempChar) != EOF) 
        ++characterCount;
    

    fclose(filePointer); /* Dosyayi kapatiyoruz */
    return characterCount;
}

int findLastSlash(char *str, int size) 
{
    int i;

    for (i = size-1; i >= 0; --i)
        if (str[i] == '/')
            return i;

    return -1;
}

int isDirectory(const char *path) 
{
    struct stat temp_stat;
    /* Get info */
    if (stat(path, &temp_stat) == -1)
        return 0;
    else
        return S_ISDIR(temp_stat.st_mode); /* Returns directory's info */
}