/*seeWhat.c*/
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

double determinant(double matrix[21][21], int size);
double computeResult1(double matrix[21][21], int size, FILE *logFilePtr);
double computeResult2(double matrix[21][21], int size, FILE *logFilePtr);
void inverse(double matrix[21][21], double inverse[21][21], int size);
void convolution(double in[11][11], double out[11][11], int size);
void delay(int seconds);
void printMatrix(double matrix[21][21], const int size, FILE *logFilePtr);
void INThandler(int sig);
void checkForCtrlC(int fifo3r, FILE *logFilePtr);

struct tm * timeinfo;

char logFile[20];
char *logFileMain="log//seeWhat.log"; /* Kendi log dosyasi */
char fifo3[] = "ctrlFIFO"; /*Fifo for communication between processes. signal=999 for Ctrl-C*/
char fifo2[] = "resFIFO"; /*Fifo for communication between seeWhat process and showResult .*/
char *fifo1; /*Main fifo*/
FILE *logFilePtr;
FILE *logFilePtrMain;
int fifo2r;

int main(int argc, char** argv) 
{ 
    
    logFile[19] = '\0';
    clock_t begin;
    clock_t end;
    double elapsedTime;
    double res;
    
    int fifo1r, fifo3r, readValue;  
    int nValue; /*Matrix size*/
    double mat[21][21];  /*Matrix array*/

    int i,j,k;
    int child, childpid;
    if (argc != 2 ) 
    {
        printf("\n#################### USAGE #########################\n");
        printf("\n-You need enter the main fifo  name  as first  argument");
        printf("\n\n-Sample");
        printf("\n./seeWhat <mainpipename>\n");
        return 0;
    } 


   /* Set the SIGINT (Ctrl-C) signal handler to intHandler */     
    signal(SIGINT, INThandler);
    
    fifo1 = (char*) malloc((strlen(argv[1]) + 1) * sizeof(char));
    for (i=0; i<strlen(argv[1]); i++){
        fifo1[i] = argv[1][i];
    }
    fifo1[i] = '\0';
    

    /*Open log file*/
    j = getpid(); 
    nValue = j;
    /* Create  Ctrl-C fifo*/
    fifo3r = open(fifo3,O_RDWR|O_NONBLOCK);
    mkfifo(fifo2, 0666);
    fifo2r = open(fifo2, O_RDWR);

    srand((unsigned)time(NULL));
        
    while(1) 
    {
        /*File created for seeWhat processes.*/
        logFilePtrMain = fopen(logFileMain,"a");
        /*Wait for main fifo creation*/    
        checkForCtrlC(fifo3r, logFilePtrMain);
        delay(1000);
        while (mkfifo(fifo1, 0666) == -1) {
            checkForCtrlC(fifo3r,logFilePtrMain);
        }
        /* Open main fifo*/ 
        fifo1r = open(fifo1, O_RDWR);
        /*Signal the main process with the Pid id. to the timeServer process*/

        while (j==nValue ){
            write(fifo1r, &j, sizeof (j));
            delay(100);
            /*Read the matrix size*/
            checkForCtrlC(fifo3r, logFilePtrMain);
            i=read(fifo1r, &nValue, sizeof (nValue));
        }
        /* Read matrix from the timeServer process.*/
        for (i=1;i<=nValue;i++) 
            for (j=1;j<=nValue;j++){
                k=0;
                while (k==0) {
                    checkForCtrlC(fifo3r, logFilePtrMain); /*Wait for an element*/
                    k=read(fifo1r, &readValue, sizeof (readValue));                 
                }
                mat[i][j] = readValue;
            }
        close(fifo1r);
        unlink(fifo1); /*Remove the fifo for next pass*/
        fclose(logFilePtrMain);
        logFilePtrMain = NULL;

        child = fork();
        if (child == 0) 
        {
            i = sprintf (logFile,"log//seeWhat_%d.log", getpid());

            /*File created for seeWhat processes.*/
            logFilePtr = fopen(logFile,"w");

            srand((unsigned)time(NULL));
            childpid = getpid();
            checkForCtrlC(fifo3r, logFilePtr);
            write(fifo2r, &childpid, sizeof(childpid));
            /* RESULT 1 */
            begin = clock();
            res = computeResult1(mat, nValue, logFilePtr);
            end = clock();
            elapsedTime = (double)(end - begin) / CLOCKS_PER_SEC*1000;
            write(fifo2r, &res, sizeof(res));
            write(fifo2r, &elapsedTime, sizeof(elapsedTime));
            checkForCtrlC(fifo3r, logFilePtr);
            /* RESULT 2 */
            begin = clock();
            res = computeResult2(mat, nValue, logFilePtr);
            end = clock();
            elapsedTime = (double)(end - begin) / CLOCKS_PER_SEC*1000;
            write(fifo2r, &res, sizeof(res));
            write(fifo2r, &elapsedTime, sizeof(elapsedTime));
            
            fclose(logFilePtr);
            logFilePtr = NULL;
            close(fifo3r);
            close(fifo2r);
            free(fifo1);
            exit(EXIT_SUCCESS);
        }
    }    
    return 0;
}


void printMatrix(double matrix[21][21], const int size, FILE *logFilePtr)
{
    int i,j;
    fprintf(logFilePtr, "[");
    for (i=1; i<=size; i++) 
    {
        for (j=1; j<=size; j++)
            fprintf(logFilePtr, "%7.4lf ",matrix[i][j]);
        fprintf(logFilePtr, ",");
    }
    fprintf(logFilePtr, "]");
}

void checkForCtrlC (int fifo3r, FILE *logFilePtr)
{
    int readValue,j;
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
        close(fifo2r);
        exit(0);
    }
}

void INThandler(int sig)
{
    int fifowr;
    int cSignal = 999;

    if (logFilePtr != NULL)
    {
        fclose(logFilePtr);
    }

    if (logFilePtrMain == NULL)
    {
        logFilePtrMain = fopen(logFileMain, "a");
    }
    fifowr = open(fifo3, O_WRONLY);
    /*Ctrl-C detected. Signal other process for Ctrl-C */ 

    write(fifowr, &cSignal, sizeof(cSignal));
    close(fifowr);
    fprintf(logFilePtrMain,"Ctrl-C entered for pid = %d\nExiting", getpid());
    fclose(logFilePtrMain);
    if (fifo1 != NULL) 
    {
        free(fifo1);
        fifo1 = NULL;
    }
    close(fifo2r);
    exit(0); 
}

void delay(int seconds)
{
    clock_t endwait;
    endwait = clock () + seconds * CLOCKS_PER_SEC/1000 ;
    while (clock() < endwait) {}
}

/*Compute Result1 */
double computeResult1(double matrix[21][21], int size, FILE *logFilePtr)
{

    double detOrj, detInv = 0;
    double subMatrix[21][21], inverseSubmatrix[21][21], inverseMatrix[21][21];
    int i, j, nSize;

    nSize = size / 2;
    fprintf(logFilePtr, "Orjinal Matris\n");
    printMatrix(matrix, size, logFilePtr);
    detOrj = determinant(matrix, size); /*Determinant of original matrix*/

    /*Divide main matrix into four sub matrixes*/

    /* Left upper part*/
    for (i=1; i<=nSize; i++)
        for (j=1; j<=nSize; j++)
            subMatrix[i][j] = matrix[i][j];
    inverse(subMatrix, inverseSubmatrix, nSize);
    for (i=1; i<=nSize; i++)
        for (j=1; j<=nSize; j++)
            inverseMatrix[i][j] = inverseSubmatrix[i][j];

    /* Right  upper part*/
    for (i=1; i<=nSize; i++)
        for (j=1; j<=nSize; j++)
            subMatrix[i][j] = matrix[i][j+nSize];
    inverse(subMatrix, inverseSubmatrix, nSize);
    for (i=1; i<=nSize; i++)
        for (j=1; j<=nSize; j++)
            inverseMatrix[i][j+nSize] = inverseSubmatrix[i][j];

    /* Left lower part*/
    for (i=1; i<=nSize; i++)
        for (j=1; j<=nSize; j++)
            subMatrix[i][j] = matrix[i+nSize][j];
    inverse(subMatrix, inverseSubmatrix, nSize);
    for (i=1; i<=nSize; i++)
        for (j=1; j<=nSize; j++)
            inverseMatrix[+i+nSize][j] = inverseSubmatrix[i][j];

    /* Right lower part*/
    for (i=1; i<=nSize; i++)
        for (j=1; j<=nSize; j++)
            subMatrix[i][j] = matrix[i+nSize][j+nSize];
    inverse(subMatrix, inverseSubmatrix, nSize);
    for (i=1; i<=nSize; i++)
        for (j=1; j<=nSize; j++)
            inverseMatrix[i+nSize][j+nSize] = inverseSubmatrix[i][j];

    fprintf(logFilePtr, "\nShifted Inverse Matris\n");
    printMatrix(inverseMatrix, size, logFilePtr);
    detInv=determinant(inverseMatrix, size); /*Determinant of original matrix*/
    return (detOrj - detInv);
}

/*Compute Result2 */
double computeResult2(double matrix[21][21], int size, FILE *logFilePtr)
{

    double detOrj, detInv = 0;
    double subMatrix[11][11], inverseSubmatrix[11][11], inverseMatrix[21][21];
    int i, j, nSize;


    nSize = size / 2;
    detOrj = determinant(matrix, size); /*Determinant of original matrix*/

    /*Divide main matrix into four sub matrixes*/

    /* Left upper part*/
    for (i=1; i<=nSize; i++) 
        for (j=1; j<=nSize; j++)
            subMatrix[i][j] = matrix[i][j];
  
    convolution(subMatrix, inverseSubmatrix, nSize);
    
    for (i=1; i<=nSize; i++)
        for (j=1; j<=nSize; j++)
            inverseMatrix[i][j] = inverseSubmatrix[i][j];

    /* Right  upper part*/
    for (i=1; i<=nSize; i++)
        for (j=1; j<=nSize; j++)
            subMatrix[i][j] = matrix[i][j+nSize];
    convolution(subMatrix, inverseSubmatrix, nSize);
    for (i=1;i<=nSize;i++)
        for (j=1;j<=nSize;j++)
            inverseMatrix[i][j+nSize]=inverseSubmatrix[i][j];

    /* Left lower part*/
    for (i=1; i<=nSize; i++)
        for (j=1; j<=nSize; j++)
            subMatrix[i][j] = matrix[i+nSize][j];
    convolution(subMatrix, inverseSubmatrix, nSize);
    for (i=1; i<=nSize; i++)
        for (j=1; j<=nSize; j++)
            inverseMatrix[+i+nSize][j] = inverseSubmatrix[i][j];

    /* Right lower part*/
    for (i=1; i<=nSize; i++)
        for (j=1; j<=nSize; j++)
        subMatrix[i][j]=matrix[i+nSize][j+nSize];
    convolution(subMatrix, inverseSubmatrix, nSize);
    for (i=1;i<=nSize;i++)
        for (j=1;j<=nSize;j++)
            inverseMatrix[i+nSize][j+nSize]=inverseSubmatrix[i][j];


    fprintf(logFilePtr,"\nConvolution Matris\n");
    printMatrix(inverseMatrix, size, logFilePtr);
    detInv=determinant(inverseMatrix, size); /*Determinant of convolution matrix*/
    return (detOrj-detInv);
}

double determinant(double matrix[21][21], int size)
{ 
    double tmp[21][21];
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
                if (tmp[i][i]==0)
                    ratio=0;
                else ratio = tmp[j][i] / tmp[i][i];
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

/*Find the inverse of matrix with Gauss-Jordan Elimination Method */
void inverse(double matrix[21][21], double inverted[21][21], int size)
{ 
    int i, j, k;
    double a[42][42], d;

    for(i=1; i<41; i++)
        for(j=1; j<41; j++)
            a[i][j] = 0;

    for(i=1; i<=size; i++)
        for(j=1; j<=size; j++)
            a[i][j] = matrix[i][j];

   for(i=1; i<=size; i++)
        for(j=1; j<=2*size; j++)
            if(j == (i+size))
                a[i][j] = 1;

    /************** partial pivoting **************/
    for(i=size; i>1; i--)
    {
        if(a[i-1][1] < a[i][1])
        for(j=1; j<=size*2; j++)
        {
            d = a[i][j];
            a[i][j] = a[i-1][j];
            a[i-1][j] = d;
        }
    }

    /********** reducing to diagonal  matrix ***********/
    for(i=1; i<=size; i++)
    {
        for(j=1; j<=size*2; j++)
        if(j != i)
        {
            if (a[i][i] == 0) 
                 d = 1;
            else d = a[j][i] / a[i][i];
            for(k=1; k<=size*2; k++)
                a[j][k] -= a[i][k] * d;
        }
    }

    /************** reducing to unit matrix *************/
    for(i=1; i<=size; i++)
    {
        d = a[i][i];
        if (d == 0) 
            d = 1;

        for(j=1; j<=size*2; j++)
            a[i][j] = a[i][j] / d;
    }

    for(i=1; i<=size; i++)
    {
        for(j=size+1; j<=size*2; j++)
            inverted[i][j-size] = a[i][j];
    }
}

/* Find the convolution matrix. */
void convolution(double in[11][11], double out[11][11], int size)
{
    int i, j, m, n, mm, nn, ii, jj, center;
    double kernel[3][3] = {{1,0,0},
                          {0,1,0},
                          {0,0,1}};
    for (i=0; i<11; i++)
        for (j=0; j<11; j++)
            out[i][j] = 0;

    /* find center position of kernel (half of kernel size) */
    center = size / 2;
                
    /*Create convolution matrix. */
    for(i=1; i <= size; ++i)              
    {
        for(j=1; j <= size; ++j)          
        {
            for(m=1; m <= 3; ++m)     
            {
                /* row index of flipped kernel */
                mm = size - 1 - m;      
                /*Kernel columns */
                for(n=1; n <= 3; ++n) 
                {
                    nn = size - 1 - n;  
                    /* index of input signal, used for checking boundary*/
                    ii = i + (m - center);
                    jj = j + (n - center);
                    if (mm < 0) mm = 1;
                    if (nn < 0) nn = 1;
                    if (ii < 0) ii = 1;
                    if (jj < 0) jj = 1;
                    /* ignore input samples which are out of bound */
                    if( ii >= 1 && ii <= size && jj >= 1 && jj <= size )
                        out[i][j] += in[ii][jj] * kernel[mm][nn];
                }
            }   
        }
    }
}
