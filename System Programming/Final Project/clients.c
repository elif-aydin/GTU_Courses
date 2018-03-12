#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/errno.h>

/* Messages */
#define CLIENTS_INFORMATION '1'
#define DEAD_MESSAGE '9'
#define MESSAGE_INITIALIZE 'F';

int mainPid; /*Main pid*/ 
int read_file_thread; /*Read file thread self id*/
int flag = 0; /*Process flag to finish complete current process*/
int clientCount = 0; /*Client counter*/
int serverSocket; /* Server socket */

pthread_t waitingThread;
pthread_mutex_t clientMutex = PTHREAD_MUTEX_INITIALIZER; /*Client mutex to synchronization*/

clock_t startTime; /*timeval structure*/
clock_t endTime; /*To get connection time clients*/

double runDurations[50];


/*
 * Thread function of waits server message 
 */
void* waitForRead(void *data);

/*
 * Signal handler for client process
 */
static void signalHandler(int signal_number);

double calculateStandartDeviation(double data[50], int n);


/*
 * Calculates different two times (Use timeval structure)
 */
double timedifference_milliseconds(clock_t start, clock_t finish) ;


/** Main **/
int main(int argc, char** argv) 
{
    struct sockaddr_in serverAddress;
    pid_t clientPid;
    int clientID;
    char inputFileName[512] = "";
    char message[1];
    char cmd[50];
    FILE *filePointer;
    struct sigaction act;
    char* ipAddress = "127.0.0.1";
    int portNum = 5000;
    int m, n, q, i, j, k;

    if (argc != 5 ) 
    {
        fprintf(stderr, "\nYou need enter 4 arguments \n");
        fprintf(stderr, "Usage\n");
        fprintf(stderr, "./clients <#of columns of A, m>   <#of rows of A, p>   <#of clients, q>  <port #, id>\n");
        fprintf(stderr, "#of clients should be less than 50\n");
        exit(EXIT_FAILURE);
    }
    
    if (atoi(argv[1]) > 20 || atoi(argv[2])  > 20  || atoi(argv[3])  > 50) 
    {
        fprintf(stderr, "\nMatrix should have maximum size 20X19 \n");
        fprintf(stderr, "  Max #of clients 50\n");
        exit(EXIT_FAILURE);
    }

    /* Gets main arguments */
    m = atoi(argv[1]);
    n = atoi(argv[2]);
    q = atoi(argv[3]);
    portNum = atoi(argv[4]);

    /* Set signal handler */
    act.sa_handler = signalHandler;
    act.sa_flags = 0;

    if ((sigemptyset(&act.sa_mask) == -1) || (sigaction(SIGINT, &act, NULL) == -1)  || (sigaction(SIGUSR1, &act, NULL) == -1) || (sigaction(SIGPIPE, &act, NULL) == -1)
        || (sigaction(SIGQUIT, &act, NULL) == -1)|| (sigaction(SIGHUP, &act, NULL) == -1)  || (sigaction(SIGTERM, &act, NULL) == -1)) 
    {
        perror("Signal set error happened !!");
        exit(EXIT_FAILURE);
    }

    /*Get process pid*/
    clientPid = getpid();
    mainPid = getpid();
    
    /*Open client log file*/
    sprintf(inputFileName, "client_%d.log", clientPid);
    filePointer = fopen(inputFileName, "a");

    /* Socket setup */
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0) 
    {
        perror("Create socket error happened!");
        exit(EXIT_FAILURE);
    }

    /*Memory initialize*/
    memset(&serverAddress, 0, sizeof (struct sockaddr_in));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNum);
    inet_pton(AF_INET, ipAddress, &serverAddress.sin_addr);
    
    startTime = clock();
    if (connect(serverSocket, (struct sockaddr *) &serverAddress, sizeof (serverAddress)) < 0) 
    {
        fprintf(stderr, "Server is not available right now\n\n");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    clientPid = clientPid * 10000 + m * 100 + n;

    /* Write matrix size to socket */
    write(serverSocket, &clientPid, sizeof (pid_t));
    read(serverSocket, &clientID, sizeof (int));

    fprintf(stderr, "\nConnection to the server : Successful");
    fprintf(stderr, "\nClient id                : %d\n", (int) getpid());

    /*Create thread */
    if (pthread_create(&waitingThread, NULL, waitForRead, NULL) != 0) 
    {
        perror("Error in pthread_create happened!");
        exit(EXIT_FAILURE);
    }
    pthread_detach(waitingThread);
    pthread_join(waitingThread, NULL);
    pthread_mutex_lock(&clientMutex);

    /* Read matrix from the server */
    fprintf(filePointer,"Matrix A\n");
    for (i=0; i<m; i++)
    {
        for(j=0;j<n;j++)
        {
            read(serverSocket, &k, sizeof (int));
            fprintf(filePointer,"%4d",k);
        }
        fprintf(filePointer,"\n");
    }
    
    /*Read vector from the server */
    fprintf(filePointer,"\nVector b\n");
    for (i=0; i<m; i++)
    {
        read(serverSocket, &k, sizeof (int));
        fprintf(filePointer,"%4d\n",k);
    }
    
    endTime = clock();
    runDurations[0] = (((double) (endTime - startTime))*1000 / CLOCKS_PER_SEC);

    sprintf(cmd, "./clients %d %d 1&", m, n);
    if (q > 1 ) 
    {
        for (i=0; i<q-1; i++) 
        {
            startTime = clock();
            sprintf(cmd, "./clients %d %d 1 %d", m, n,portNum);
            clientID = system(cmd);
            endTime = clock();
            runDurations[i+1]= (((double) (endTime - startTime))*1000 / CLOCKS_PER_SEC)*3;
        }
    }
    
    fprintf(filePointer,"\nAverage Connection time %6.4f ms", calculateStandartDeviation(runDurations, q));
    message[0] = DEAD_MESSAGE;
    write(serverSocket, &message, 2 * sizeof (char));
    fclose(filePointer);
    return 0;
}


/*
 * Thread function of waits server message 
 */
void * waitForRead(void *data) 
{
    char message[1];
    int readRes;
    sigset_t blockMask;

    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGINT);
    sigaddset(&blockMask, SIGUSR1);
    pthread_sigmask(SIG_BLOCK, &blockMask, NULL);

    message[0] = MESSAGE_INITIALIZE;
    startTime=clock();
    read_file_thread = pthread_self();

    while (1) 
    {
        pthread_mutex_lock(&clientMutex);
        readRes = recv(serverSocket, &message, 2 * sizeof (char), MSG_DONTWAIT);
        if (readRes == -1) 
        {
            pthread_mutex_unlock(&clientMutex);
            continue;
        }

        if (message[0] == DEAD_MESSAGE) 
        {
            kill(mainPid, SIGUSR1);
            pthread_exit(NULL);
        }

        if (readRes == 0) 
        {
            fprintf(stderr, "Connection to the server was disconnected. Gonna terminate the program !\n\n");
            exit(EXIT_FAILURE);
        }

        pthread_mutex_unlock(&clientMutex);
        message[0] = MESSAGE_INITIALIZE;
    }
    endTime = clock();

}


/*
 * Signal handler for client process
 */
static void signalHandler(int signal_number) 
{
    char message[2];
    sigset_t blockMask;

    if (signal_number == SIGINT) 
    {
        sigemptyset(&blockMask);
        sigaddset(&blockMask, SIGINT);
        pthread_sigmask(SIG_BLOCK, &blockMask, NULL);
        while (flag);
    }

    if (signal_number == SIGUSR1 || signal_number == SIGINT) 
    {
        pthread_cancel(waitingThread);
        pthread_join(waitingThread, NULL);
    }

    if (signal_number == SIGINT) 
    {
        fprintf(stderr, "SIGINT signal detected. Gonna terminate the program !\n\n");
        message[0] = DEAD_MESSAGE;
        write(serverSocket, &message, 2 * sizeof (char));
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    if (signal_number == SIGUSR1) 
    {
        fprintf(stderr, "Server terminated. Gonna terminate the program !\n\n");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    if (signal_number == SIGPIPE) 
    {
        fprintf(stderr, "Connection to the server was disconnected. Gonna terminate the program !\n\n");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    if(signal_number == SIGQUIT || signal_number == SIGTERM || signal_number == SIGHUP)
    {
        fprintf(stderr, "Unexpected termination happened ! \n\n" );
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
}

/* 
 *Calculates standart deviation 
 */
double calculateStandartDeviation(double data[50], int n)
{
    double sum = 0.0, mean, standardDeviation = 0.0;
    int i;

    for(i=0; i<n; ++i)
    {
        sum += data[i];
    }

    mean = sum/10;

    for(i=0; i<n; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation/n);
}