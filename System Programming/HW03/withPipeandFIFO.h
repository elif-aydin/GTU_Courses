/* Gerekli kutuphaneler */

#include <stdio.h>
#include <stdlib.h> /* exit, malloc */
#include <string.h> /* strlen */
#include <unistd.h> /* fork */
#include <dirent.h> /* opendir closedir */
#include <sys/stat.h> /* fifo */
#include <sys/wait.h> /* wait */
#include <sys/types.h> /* pid_t */
#include <fcntl.h> /* open, close flags */


#define LOG_FILE "log.log"
#define BUFFER 1024
#define MAX_PATH 256
#define MAX_DIR 256

/* *
 * Bu fonksiyon once dosyayi acar dosyayi sonuna kadar okur ve
 * dosyadaki toplam karakter sayisini bulup return eder.
 * @param fileName karakter sayisini bulacagimiz file
 * @return characterCount dosyadaki karakter sayisi
 */
int numberOfFileSize(const char *fileName);


/**
 * Bu fonksiyon parametre olarak aldigi string i yine parametre olarak aldigi
 * file icinde arar ve buldugu her bir kelimenin basladigi yeri parametre
 * olarak aldigi dosyaya yazar.
 * @param inputFileName icinde arama yapacagimiz dosya
 * @param target icinde arayacagimiz kelime
 * @param outputFileName üzerine yazacağımız
 * @return void
 */
int listFromFile(const char *inputFileName, const char *outputFileName, const char *target, int pipeArray[2]);


/**
* Bu fonksiyon aldigi char* ın directory olup olmadigini kontrol eder.
* @param path kontrol edecegi degisken
* @return Eger directory degil ise 0 return eder. 
*/
int isDirectory(const char *path);


/**
 * Bu fonksiyon bütün alt directory leri dolasir ve verilen kelimenin toplam sayisini
 * return eder. ListFromFile i cagirir.
 */
int searchForDirectory(const char *string, char *dirPath); 

/**
 * Verilen directory icindeki toplam directory ve file sayisini bulur.
 */
void numOfObjects(const char *dirPath, int *dirCount, int *fileCount);

/**
 * Bu fonksiyon fifo olusturur.
 */
void createFifos(const char *dirPath, char charArray[MAX_DIR][MAX_PATH]);

int findLastSlash(char * str, int size);

pid_t pidFlag;
