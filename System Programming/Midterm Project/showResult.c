/*showResult.c*/
#include <stdio.h>
#include <stdlib.h>  /*exit, malloc */
#include <string.h> /* strlen */
#include <unistd.h> /* fork */
#include <sys/stat.h>
#include <sys/wait.h> /* wait */
#include <sys/types.h> /* pid_t */
#include <fcntl.h> 
#include <signal.h>
#include <time.h>


void INThandler(int sig);
void delay(int seconds);
void checkForCtrlC (int fifo3r);

struct tm * timeinfo;
char fifo2[] = "resFIFO";
char fifo3[] = "ctrlFIFO"; /*fifo for Ctrl-C .*/
char *logFile = "log//showResult.log";
FILE *logFilePtr;
int fifo2r, fifo3r;

int main(int argc, char** argv) 
{
    int i, pid;
	double res1, res2;
	double elapsedTime1, elapsedTime2;
    
     
	/*Set Ctrl-C handler routine*/ 
	signal(SIGINT, INThandler);

	/*Fifo should be creater by timeServer Process. */
	/* Open Ctrl-C communication fifo */
	fifo3r = open(fifo3, O_RDWR|O_NONBLOCK);
	
	/* Open communication  fifo3*/
	while((fifo2r = open(fifo2, O_RDONLY)) == -1)
	{
		delay(200);
		checkForCtrlC(fifo3r);
    }

	/* Open main fifo */
	while(1)
	{
		delay(100);
		/*Read for main fifo for pid.*/
		checkForCtrlC(fifo3r);
        while((i = read(fifo2r, &pid, sizeof(pid))) == 0)    			    checkForCtrlC(fifo3r);
		while((i = read(fifo2r, &res1, sizeof(res1))) == 0)  			    checkForCtrlC(fifo3r);
		while((i = read(fifo2r, &elapsedTime1, sizeof(elapsedTime1))) == 0) checkForCtrlC(fifo3r);
		while((i = read(fifo2r, &res2, sizeof(res2))) == 0) 			    checkForCtrlC(fifo3r);
		while((i = read(fifo2r, &elapsedTime2, sizeof(elapsedTime2))) == 0) checkForCtrlC(fifo3r);
		printf("PID = %d  RES1 = %8.5lf RES2 = %8.5lf\n", pid, res1, res2);
		logFilePtr = fopen(logFile, "a");
		fprintf(logFilePtr,"PID = %d RES1 = %8.5lf Elapsed for 1 = %8.5lf RES = %8.5lf Elapsed for 2 =  %8.5lf\n",pid, res1, elapsedTime1, res2, elapsedTime2);
		fclose(logFilePtr);
 	}
	return 0;
}

void delay(int seconds)
{
	clock_t endwait;
	endwait = clock () + seconds * CLOCKS_PER_SEC/1000 ;
	while (clock() < endwait) {}
}

void  INThandler(int sig)
{
    char fifo3[] = "ctrlFIFO";
	int fifowr;
	int cSignal = 999;
	FILE *logFilePtr;
	char *logFile = "log//showResult.log";
	logFilePtr = fopen(logFile, "a");

    fifowr = open(fifo3, O_WRONLY);
	/*Ctrl-C detected */    
    write(fifowr, &cSignal, sizeof (cSignal));
    close(fifowr);
    close(fifo2r);

    fprintf(logFilePtr,"Ctrl-C entered for pid = %d\nExiting", getpid());
    fclose(logFilePtr);
    exit(0); 
}

void checkForCtrlC(int fifo3r)
{
	int readValue, j;
	int cSignal = 999;
	time_t mytime;
	
	j = read(fifo3r, &readValue, sizeof(readValue));
	
	if (j>0  && readValue == 999) 
	{
		logFilePtr = fopen(logFile, "a");
		write(fifo3r, &cSignal, sizeof (cSignal));
		time(&mytime);
		timeinfo = localtime(&mytime);
		fprintf(logFilePtr,"\n\nCtrl-C received from parent process.\nExiting pid = %d date: %20s", getpid(),asctime (timeinfo));
		fclose(logFilePtr);
		close(fifo3r);
		close(fifo2r);
		exit(0);
	}
}