#include "withPipeandFIFO.h" 

int main(int argc, char** argv) 
{
    char * target = argv[1];
    char * fileName = argv[2];
    char * exeCommand = argv[0];
    int totalFound = 0;

    /* Log dosyasi uzerine surekli yazılmaması icin daha onceden kullanilan
    dosya silinir. */
    FILE * filePointer = fopen(LOG_FILE, "r");
    if (filePointer != NULL)
    {
        remove(LOG_FILE);        
        fclose(filePointer);
    }

    int value = strcmp("./withPipeandFIFO", exeCommand);
    
    /* Root process in pid si alinir. */
    pidFlag = getpid();

    /* USAGE */
    if(argc != 3 || value != 0) 
    {
        printf("\n\n------------------USAGE-------------------\n");
        printf("You need enter for executable name ->> withPipeandFIFO\n");
        printf("You need enter the string who you want search in file\n");
        printf("You need enter the file name\n\n");
        printf("-----Sample----");
        printf("\n./withPipeandFIFO target folderName\n\n");

        exit (1);
    }

    else 
        totalFound = searchForDirectory(target, fileName);


    filePointer = fopen(LOG_FILE,"a");
    if (filePointer == NULL)
    {
        perror("File could not open\n");
        fclose(filePointer);
    }

    fprintf(filePointer,"\n%d %s were found in total.",totalFound,target);
    fclose(filePointer);

    return 0;
}
