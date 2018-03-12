/*timeServer.c*/
#include <stdio.h>
#include <stdlib.h> /* exit, malloc */
#include <string.h> /* strlen */
#include <unistd.h> /* fork */
#include <sys/stat.h>
#include <sys/wait.h> /* wait */
#include <sys/types.h> /* pid_t */
#include <fcntl.h>
#include <signal.h>
#include <time.h>


void delay(int seconds);
double determinant(int matrix[21][21], int size);
void checkForCtrlC(int fifo3r, FILE *logFilePtr);
void INThandler(int sig);

struct tm * timeinfo;
char *fifo1 = NULL;
char fifo3[] = "ctrlFIFO"; /* FIFO for Ctrl-C .*/
char *logFile = "log//timeServer.log";
FILE *logFilePtr = NULL;

void printUsage()
{
		printf("\n#################### USAGE #########################\n");
        printf("\n-You need enter the ticks as first argument. It can't be 0.");
        printf("\n-You need enter the n value for matrix  as second argument (max=10) and can't be 0.");
        printf("\n-You need enter the main fifo name  as third argument");
        printf("\n\n-Sample");
        printf("\n./timerServer <ticks in miliseconds> <n> <mainpipename>\n");
}

int main(int argc, char** argv) 
{
	int readValue;
    int fifo1r, i, j, k, fifo3r;
    int mat[21][21]; 
    int nValue = 0;
    int ticks = 0;
	clock_t beginTime;
	char timeStr[64];
	timeStr[63] = '\0';
	double det;
   
   if (argc != 4)
   {
   		printUsage();
   		exit(0);
   }

	nValue = atoi(argv[2]); 
	ticks = atoi(argv[1]);

    if (nValue == 0 || ticks == 0 || nValue > 20) 
    {
        printUsage();
        exit (0);
    } 

	signal(SIGINT, INThandler); /* Sinyal gelirse sagdaki fonkiyonu cagirir. */
	fifo1 = (char*) malloc((strlen(argv[3]) + 1) * sizeof(char)); /* FIFO1 ismi parametre olarak gelir. */	

    for (i=0; i<strlen(argv[3]); i++) /* Copying main fifo name */
    	fifo1[i] = argv[3][i];
    fifo1[i] = '\0';

    nValue = 2 * nValue;


	/*Create communication fifo*/
    if (mkfifo(fifo3, 0666) == -1) 
    {
		perror("Failed to create FIFO...");
		exit(EXIT_FAILURE);
    } 

	logFilePtr = fopen(logFile, "w");

	/* Open communication  fifo3*/
    fifo3r = open(fifo3, O_RDWR|O_NONBLOCK);

	/*Randomize the seed with the current time*/
	srand((unsigned)time(NULL));

	/* Open main fifo */
	while(1)
	{
		delay(ticks);
		
		det = 0; /*Prepare a reversible matrix to send.*/
		while(det == 0) /* Determinant 0 dan farklı olana kadar matris uretilir. */
		{
			for(i=1; i<=nValue; i++)
				for(j=1; j<=nValue; j++)
				{
					k = rand() % 12 + 1;
					mat[i][j] = k;
				}
			det = determinant(mat,nValue);
		}

		/*Read for main fifo for pid.*/
		if (fifo1 == NULL) /* daha once ctrl-c gelmis olabilir digerlerini bilgilendirirken buraya gelebilir. */
		{
			continue;
		}

    	while((fifo1r = open(fifo1, O_RDONLY|O_NONBLOCK)) == -1)
    	{
    		delay(500);
    		checkForCtrlC(fifo3r, logFilePtr);
    	}

        i = read(fifo1r, &readValue, sizeof (readValue));
		close(fifo1r);
		fifo1r = open(fifo1, O_RDWR);

		/*Write the matrix size first  */
        i = write(fifo1r, &nValue, sizeof(nValue));
		for (i=1; i<=nValue; i++)
			for(j=1; j<=nValue; j++)
			{
				k = mat[i][j];
				write(fifo1r, &k, sizeof(k));
			}

		beginTime = clock();
		time(&beginTime);
		timeinfo = localtime(&beginTime);
		strftime(timeStr, sizeof(timeStr), "%c", timeinfo);
        fprintf (logFilePtr, "Matris generated in %s  PID = %d  Determinant = %lf  \n", timeStr, readValue, det);

		/*Check fifo for Ctrl-C fifo */   
		checkForCtrlC(fifo3r, logFilePtr);
	}
	
	return 0;
}

double determinant(int matrix[21][21], int size)
{ 
	double tmp[41][41];
	double ratio, det;
	int i, j, k;

	/* Conversion of matrix to upper triangular */

    for (i=1; i<=size; i++)
        for (j=1; j<=size; j++)
        tmp[i][j] = matrix[i][j];
    for(i=1; i<=size; i++)
    {
        for(j=1; j<=size; j++)
        {
            if(j > i)
            {
                if(tmp[i][i] == 0)
                	ratio = 0;
                else 
                	ratio = tmp[j][i] / tmp[i][i];

                for(k=1; k<=size; k++)
                {
                    tmp[j][k] -= ratio * tmp[i][k];
                }
            }
        }
    }
    det = 1;
    for(i=1; i<=size; i++)
        det *= tmp[i][i];
    return det;
}

void delay(int seconds)
{
	clock_t endwait;
	endwait = clock () + seconds * CLOCKS_PER_SEC/1000 ;
	while (clock() < endwait) {	}
}

void INThandler(int sig)
{
    char fifo3[] = "ctrlFIFO";
	int fifowr;
	int cSignal = 999;
	FILE *logFilePtr;
	char *logFile = "timeServer.log";

	logFilePtr = fopen(logFile,"a");
    fifowr = open(fifo3, O_RDWR);

	/*Ctrl-C detected */    
    write(fifowr, &cSignal, sizeof (cSignal));
	write(fifowr, &cSignal, sizeof (cSignal));
	close(fifowr);
    fprintf(logFilePtr, "Ctrl-C entered for pid = %d\nExiting", getpid());
    fclose(logFilePtr);
    if (fifo1 != NULL) 
    {
 		free(fifo1);
    	fifo1 = NULL;
    }
   
}
 
void checkForCtrlC (int fifo3r, FILE *logFilePtr)
{
	int readValue, j;
	int cSignal = 999;
	time_t mytime;
	j = read(fifo3r, &readValue, sizeof(readValue));

	if (j>0  && readValue == 999) 
	{
		write(fifo3r, &cSignal, sizeof (cSignal));
		close(fifo3r);
		time(&mytime);
		timeinfo = localtime (&mytime);
		fprintf(logFilePtr, "\n\nCtrl-C received from parent process.\nExiting pid = %d date: %20s", getpid(),asctime (timeinfo));
		fclose(logFilePtr);
		if (fifo1 != NULL) 
	    {
	 		free(fifo1);
	    	fifo1 = NULL;
	    }
		exit(0);
	}
}