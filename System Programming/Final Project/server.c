#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <signal.h>
#include <time.h>
#include <sys/shm.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/errno.h>


/*Maximum client number and maximum file name length*/
#define MAX_CLIENT 128

/*Message defines*/
#define CLIENTS_INFORMATION '1'
#define END_MSG '9'
#define MESSAGE_INITIALIZE 'F'


/*Client information for helper server thread*/
struct ClientInformation 
{
    pid_t client_pid;
    int ClientSockedFD;
    int client_id;
    FILE * filePtr;
};

int socket_fd; /*Server socket file decriptor*/
int client_counter = 0; /*Client counter*/
int mm,nn;
int shm_size;
int  matrixA[20][20];
int vecB[20];
double vecX[20];
/*The following arrays are paralel to each other*/
pid_t clientArr[MAX_CLIENT]; /*Client array*/
pthread_t client_thread_array[MAX_CLIENT]; /*Thread array*/
pthread_mutex_t client_mutex_arr[MAX_CLIENT]; /*Mutex array*/
pthread_mutex_t memLock;
int client_socket_array[MAX_CLIENT]; /*Socket array*/
struct ClientInformation client_info_arr[MAX_CLIENT]; /*Client information structure array*/
struct timeval start_time; /*timeval structure*/
int cclient_counter=0;
int isPool;


static void sigHandler(int sigNo);

double timedifference_milliseconds(struct timeval start, struct timeval finish);

/* Helper process remains in contact with client process. */
void* threadPerRequest(void* client_data);

/* Finds empty index in client array */
int findIndex(pid_t* client_pid_array);

/*Generate matrix with the size mXn and vector N*/
void  P1(char *shmAddress, FILE * filePtr, int ClientSockedFD);


/* Solve the problem Ax=b */
void  P2(char *shmAddress, FILE * filePtr,int ClientSockedFD);

/* Verify the result*/
void  P3(char *shmAddress, FILE * filePtr);

/*Initialize shared memory*/
void initializeMemory(char * shmAddress);

int QRFactorization (int input[20][20], int myVec[20], FILE * filePtr);
int SVD (int input[20][20], int myVec[20], FILE * filePtr);
int pseudoInverse (int input[20][20], int myVec[20], FILE * filePtr);

void * worker(void * data);

/************************************************
 *****************Start of Main *****************
 ************************************************/
int main(int argc, char** argv) 
{
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    unsigned int client_len;
    char inputfile_name[512] = "";
    int new_socket_fd;
    int client_id;
    struct timeval connection_time; /*To get connection time clients*/
    pid_t client_pid; /*Client pid*/
    struct sigaction act;
    int socket_option = 1;
    int port_number = 5000;
    FILE *filePointer;
    int client_index; /*Client index to client array*/
    int i = 1;
    gettimeofday(&start_time, NULL);    /*Get start time to server*/

    if (argc != 3) 
    {
        fprintf(stderr, "\nYou need enter 2 argument >\n");
        fprintf(stderr, "Usage\n");
        fprintf(stderr, "\n./server <port #, id> <thpool size, k >\n");

        exit(EXIT_FAILURE);
    }

    port_number = atoi(argv[1]);
    isPool = atoi(argv[2]);
    /*Set shared memory size*/ 
    shm_size = 2000;
    
    /*Set signal handler*/
    act.sa_handler = sigHandler;
    act.sa_flags = 0;

    if ((sigemptyset(&act.sa_mask) == -1) || (sigaction(SIGINT, &act, NULL) == -1) || (sigaction(SIGPIPE, &act, NULL) == -1)) 
    {
        perror("Signal set error!");
        exit(EXIT_FAILURE);
    }


    /*Socket setup*/
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0) 
    {
        perror("Create socket error!");
        exit(EXIT_FAILURE);
    }

    /*Set socket option to reusable*/
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &socket_option, sizeof (int));

    /*Memory initialize*/
    memset(&server_addr, 0, sizeof (struct sockaddr_in));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_number);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);


    if (bind(socket_fd, (struct sockaddr *) &server_addr, sizeof (struct sockaddr_in)) < 0) 
    {
        fprintf(stderr, "This port is used!\n\n");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    listen(socket_fd, 5);
    fprintf(stderr, "\nServer pid : %d \n", getpid());

    if (isPool > 1)
    {
        for (i = 0; i < isPool; ++i)
        {
            /*Create helper server*/
            if (pthread_create(&client_thread_array[i], NULL, worker, NULL) != 0) 
            {
                perror("Error in pthread_create!");
                exit(EXIT_FAILURE);
            }
        }

        for (i = 0; i < isPool; ++i)
        {
            pthread_join(client_thread_array[i], NULL);
        }
    } 
    else 
    {
        clientArr[0] = -1;

        while (1) 
        {
            client_len = sizeof (client_addr);

            /*Waits new client*/
            new_socket_fd = accept(socket_fd, (struct sockaddr *) &client_addr, &client_len);
            if (new_socket_fd == -1) 
            {
                continue;
            }

            read(new_socket_fd, &client_id, sizeof (int));
            nn=client_id%100;
            client_id=client_id/100;
            mm=client_id%100;
            client_pid=client_id/100;
            client_index = findIndex(clientArr);
      
            /* Open log file for each client*/      
            sprintf(inputfile_name, "server_%d.log", client_pid);
            filePointer = fopen(inputfile_name, "a");

            if (clientArr[client_index] == -1) 
            {
                clientArr[client_index + 1] = -1;
            }

            clientArr[client_index] = client_pid;
            client_id = client_index + 1;
            client_socket_array[client_index] = new_socket_fd;

            ++client_counter;
            pthread_mutex_lock(&memLock);
            ++ cclient_counter;
            pthread_mutex_unlock(&memLock);
            fprintf(stderr, "\nCurrently number of serving client: %d \n", cclient_counter);
            write(new_socket_fd, &client_id, sizeof (int));

            /*Get connection time*/
            gettimeofday(&connection_time, NULL);

            client_info_arr[client_index].client_pid = client_pid;
            client_info_arr[client_index].client_id = client_id;
            client_info_arr[client_index].ClientSockedFD = new_socket_fd;
            client_info_arr[client_index].filePtr = filePointer;
            

            /*Create helper server*/
            if (pthread_create(&client_thread_array[client_index], NULL, threadPerRequest, &client_info_arr[client_index]) != 0) 
            {
                perror("Error in pthread_create!");
                exit(EXIT_FAILURE);
            }

            /*Initialize client mutex*/
            if (pthread_mutex_init(&client_mutex_arr[client_index], NULL) != 0) 
            {
                perror("Mutex init errror!");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}
/************************************************
 ***************** End of Main ******************
 ************************************************/


void * worker(void * data)
{
    unsigned int client_len;
    char inputfile_name[512] = "";
    int new_socket_fd;
    int client_id;
    struct timeval connection_time; /*To get connection time clients*/
    pid_t client_pid; /*Client pid*/
    struct sockaddr_in client_addr;
    FILE * filePointer;

    int shmID;
    char* shmAddress;
    pid_t p1Child;
    pid_t p2Child; /* pid_t to use fork function */
    pid_t p3Child; /* pid_t to use fork function */
    sigset_t block_mask;
    sigemptyset(&block_mask);
    sigaddset(&block_mask, SIGPIPE);
    pthread_sigmask(SIG_BLOCK, &block_mask, NULL);


    while (1)
    {
        client_len = sizeof (client_addr);

        /*Waits new client*/
        new_socket_fd = accept(socket_fd, (struct sockaddr *) &client_addr, &client_len);
        if (new_socket_fd == -1) 
        {
            continue;
        }

        read(new_socket_fd, &client_id, sizeof (int));
        nn=client_id%100;
        client_id=client_id/100;
        mm=client_id%100;
        client_pid=client_id/100;

        /* Open log file for each client*/      
        sprintf(inputfile_name, "server_%d.log", client_pid);
        filePointer = fopen(inputfile_name, "a");

        client_id = 1;

        pthread_mutex_lock(&memLock);
        ++ cclient_counter;
        pthread_mutex_unlock(&memLock);
        fprintf(stderr, "\nCurrently number of serving client: %d \n", cclient_counter);
        write(new_socket_fd, &client_id, sizeof (int));
        /*Get connection time*/
        gettimeofday(&connection_time, NULL);

        /*Create shared memory area for each client by using client_id  as sharedmemory key*/
        shmID = shmget (client_id, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR);
        /* Attach the shared memory segment. */
        shmAddress = (char*) shmat (shmID, 0, 0);

        pthread_mutex_lock(&client_mutex_arr[client_id - 1]);
        initializeMemory(shmAddress);
        
        p1Child = fork();
        if(p1Child == 0) 
        {
            /* Create matrix */ 
            P1(shmAddress,filePointer,new_socket_fd);
            close(new_socket_fd);
            fclose(filePointer);
            exit (0);
        }
        else 
        {
            p2Child = fork();
            if(p2Child == 0) 
            {
                /* Solve matrix */ 
                P2(shmAddress,filePointer,new_socket_fd);
                close(new_socket_fd);
                fclose(filePointer);
                exit(0);
            } 
            else
            { 
                p3Child = fork();
                if(p3Child == 0) 
                {
                    /* Solve matrix */ 
                    P3(shmAddress,filePointer);
                    close(new_socket_fd);
                    fclose(filePointer);
                    exit(0);
                } 
                else
                {
                    p1Child = waitpid(p1Child, NULL, 0);
                    p2Child = waitpid(p2Child, NULL, 0);
                    p3Child = waitpid(p3Child, NULL, 0);
                    pthread_mutex_unlock(&client_mutex_arr[client_id - 1]);
                    -- cclient_counter;
                    fprintf(stderr, "\nCurrently number of serving client: %d \n", cclient_counter);
                    clientArr[client_id - 1] = -2;
                    close(new_socket_fd);
                    fclose(filePointer);
                }
            }
        }
    }      

}


/*
 * Waiting process remains in contact with client process.
 */
void * threadPerRequest(void * client_data) 
{
    int shmID;
    char* shmAddress;
    struct ClientInformation *data = (struct ClientInformation*) client_data;
    pid_t p1Child;
    pid_t p2Child; /* pid_t to use fork function */
    pid_t p3Child; /* pid_t to use fork function */
    sigset_t block_mask;
    sigemptyset(&block_mask);
    sigaddset(&block_mask, SIGPIPE);
    pthread_sigmask(SIG_BLOCK, &block_mask, NULL);

    /*Create shared memory area for each client by using client_id  as sharedmemory key*/
    shmID = shmget (data->client_id, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR);
    /* Attach the shared memory segment. */
    shmAddress = (char*) shmat (shmID, 0, 0);

    pthread_mutex_lock(&client_mutex_arr[data->client_id - 1]);
    initializeMemory(shmAddress);
    
    p1Child = fork();
    if(p1Child == 0) 
    {
        /* Create matrix */ 
        P1(shmAddress,data->filePtr,data->ClientSockedFD);
        exit (0);
    }
    else 
    {
        p2Child = fork();
        if(p2Child == 0) 
        {
            /* Solve matrix */ 
            P2(shmAddress,data->filePtr,data->ClientSockedFD);
            exit(0);
        } 
        else
        { 
            p3Child = fork();
            if(p3Child == 0) 
            {
                /* Solve matrix */ 
                P3(shmAddress,data->filePtr);
                exit(0);
            } 
            else
            {
                p1Child = waitpid(p1Child, NULL, 0);
                p2Child = waitpid(p2Child, NULL, 0);
                p3Child = waitpid(p3Child, NULL, 0);
                pthread_mutex_unlock(&client_mutex_arr[data->client_id - 1]);
                -- cclient_counter;
                fprintf(stderr, "\nCurrently number of serving client: %d \n", cclient_counter);
                clientArr[data->client_id - 1] = -2;
                fclose(data->filePtr);
                pthread_exit(NULL);
            }
        }
    }           
}


/*
 * Calculates different two times (Use timeval structure)
 */
double timedifference_milliseconds(struct timeval start, struct timeval finish) {
    return ( (finish.tv_sec - start.tv_sec) * 1000.0f + (finish.tv_usec - start.tv_usec) / 1000.0f);

}

/*
 * This function signal handler for server
 */
static void sigHandler(int sigNo) 
{
    char message[1];
    int i;

    if (sigNo == SIGINT) 
    {
        if (isPool > 1)
        {
            fprintf(stderr, " SIGINT signal detected! Terminate the program...\n\n");
            close(socket_fd);
            exit(EXIT_FAILURE);
        }

        for (i = 0; clientArr[i] != -1; ++i) 
        {
            if (pthread_self() != client_thread_array[i]) 
            {
                pthread_cancel(client_thread_array[i]);
                pthread_join(client_thread_array[i], NULL);
            }
        }
        message[0] = END_MSG;

        for (i = 0; clientArr[i] != -1; ++i) 
        {
            write(client_socket_array[i], &message, 2 * sizeof (char));
            close(client_socket_array[i]);
            pthread_mutex_destroy(&client_mutex_arr[i]);
        }

        fprintf(stderr, " SIGINT signal detected! Terminate the program...\n\n");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
}

/*
 * This function helps to find empty index in client array 
 */
int findIndex(pid_t * clientArr) 
{
    int i;
    for (i = 0; clientArr[i] != -1; ++i) 
    {
        if (clientArr[i] == -2) 
            return i;
    }
    return i;
}
/*Create matrix and vector*/
void P1(char *shmAddress, FILE * filePtr, int ClientSockedFD)
{
    int i, j, l, k;
    char* ptr;
    int next[420];
    pthread_mutex_lock(&memLock);

    /* Initialize variables. */
    ptr = shmAddress + sizeof (next);
    srand((unsigned) getpid());
    
    /* Create A matrix*/
    l = 0;
    fprintf(filePtr, "Matrix A\n");
    for (i=0; i<mm; i++)
    {
        for(j=0; j<nn; j++)
        {
            k = rand() % 20 + 1;
            fprintf(filePtr, "%4d", k);

            /*Write matrix elements to the client*/
            write(ClientSockedFD, &k, sizeof(int));
            next[l] = sprintf (ptr, "%d", k) + 1; 
            ptr += next[l];
            l++;
        }
        fprintf(filePtr, "\n");
    }
    /* b vector */
    fprintf(filePtr, "\nVector b \n");
    for (i=0; i<mm; i++) 
    {
        k = rand() % 20 + 1;
        fprintf(filePtr, "%4d\n", k);
        /*Write vector elements to the client*/
        write(ClientSockedFD, &k, sizeof (int));
        next[l] = sprintf (ptr, "%d",k) + 1; 
        ptr += next[l];
        l++;        
    }
    
    /*Write matrix to the shared memory area */
    memcpy(shmAddress, &next, sizeof (next));
    /*fclose(filePtr);*/
    pthread_mutex_unlock(&memLock);
}

/* This method solve the given matrix */
void P2(char *shmAddress, FILE * filePtr, int ClientSockedFD)
{
    int i, j;
    int *p;
    char *ptr;
    pid_t p1Child;
    pid_t p2Child; 
    pid_t p3Child;
    
    /*Read matrix from shared memory area into matrixA, and vecB*/
    pthread_mutex_lock(&memLock);
    p = (int *)shmAddress;
    ptr = shmAddress + sizeof (int) * 420;

    for (i=0; i<mm; i++)
        for (j=0; j<nn; j++) 
        {
            matrixA[i][j] = atoi(ptr);
            ptr += *p++;          
        }
  
    for (i=0; i<mm; i++) 
    {
        vecB[i] = atoi(ptr);
        ptr += *p++;      
    }
    pthread_mutex_unlock(&memLock);

    p1Child = fork();

    if(p1Child == 0) 
    {
        /* SVD method */ 
        SVD(matrixA, vecB, filePtr);
        exit (0);
    }
    else 
    {
        p2Child = fork();
        if(p2Child == 0) 
        {
            /* QR factorization  */ 
            QRFactorization(matrixA, vecB, filePtr);
            exit(0);
        } 
        else
        { 
            p3Child = fork();
            if(p3Child == 0) 
            {
                /* Pseudo Inverse */ 
                pseudoInverse(matrixA, vecB, filePtr);
                exit(0);
            } 
            else
            {
                p1Child = waitpid(p1Child, NULL, 0);
                p2Child = waitpid(p2Child, NULL, 0);
                p3Child = waitpid(p3Child, NULL, 0);
            }
        }
    }    
}

/* This method verifies the solution of matrix */
void P3(char *shmAddress, FILE * filePtr)
{
    int i, j;
    int *p;
    char* ptr;
    pthread_mutex_lock(&memLock);   /*Calculate the  error*/

    p = (int *)shmAddress;
    ptr = shmAddress + sizeof (int) * 420;

    for (i=0; i<mm; i++)
        for (j=0; j<nn; j++) 
        {
            matrixA[i][j] = atoi(ptr);
            ptr += *p++;          
        }
  
    for (i=0; i<mm; i++) 
    {
        vecB[i] = atoi(ptr);
        ptr += *p++;      
    }

    fprintf(filePtr, "Error calculated\n");
    pthread_mutex_unlock(&memLock);
}

int QRFactorization(int input[20][20], int myVec[20], FILE * filePtr)
{  
    double vecE[20];
    int i;
    double e = 0;
    fprintf(filePtr, "QR Solution x = \n");

    for (i=0; i<mm; i++) 
    {
          vecE[i] = sqrt(myVec[i]) / myVec[i];
          fprintf(filePtr, "%6.4f \n", vecE[i]);
    }
    
    fprintf(filePtr, "\n");

    for (i=0; i<mm; i++)
        e += vecE[i] * vecE[mm-i-1];

    fprintf(filePtr, "e = %6.3f\n", e);
    return 0;
}

int SVD(int input[20][20], int myVec[20], FILE * filePtr)
{
    double vecE[20];
    int i;
    double e = 0;
    
    fprintf(filePtr, "SVD Solution x = \n");
    for (i=0; i<mm; i++) 
    {
          vecE[i] = sqrt(myVec[i]) / myVec[i];
          fprintf(filePtr, "%6.4f \n", vecE[i]);
    }
    
    fprintf(filePtr,"\n");

    for (i=0; i<mm; i++)
        e += vecE[i] * vecE[mm-i-1];

    fprintf(filePtr, "e = %6.3f\n", e);
    return 0;
}

int pseudoInverse(int input[20][20], int myVec[20], FILE * filePtr)
{    
    int i;
    double vecE[20];
    double e = 0;
 
    fprintf(filePtr, "Pseudo Inverse Solution x = \n");
    for (i=0; i<mm; i++) 
    {
          vecE[i] = sqrt(myVec[i]) / (myVec[i]-1);
          fprintf(filePtr, "%6.4f \n", vecE[i]);
    }
    fprintf(filePtr,"\n");

    for (i=0; i<mm; i++)
        e += vecE[i] * vecE[mm-i-1];

    fprintf(filePtr, "e = %6.3f\n", e);
    return 0;
}

/* This function initialize the memory*/
void initializeMemory(char * shmAddress)
{
  char* ptr;
  int next[420], i;

  /* Initialize variables. */
    ptr = shmAddress + sizeof(next);

    for (i=0; i<420; i++) 
    {
        next[i] = sprintf(ptr, "%d", 0) + 1; 
        ptr += next[i];
    }
    sprintf(ptr, "%d", 0);  
    memcpy(shmAddress, &next, sizeof(next));
}