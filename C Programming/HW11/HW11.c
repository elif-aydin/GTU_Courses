/*************************************************************
 * HW11                                                      *
 * Student Name: Elif Seyma ARMAGAN                          *
 * Student ID  : 151044042                                   *
 * Date        : 14/05/2016                                  *
 * Description : This function that takes a binary filename  *
 *  and output array parameter and returns the decoded data  *
 *  structure. It returns an array of integers               *
 *  for the data types according to the following            *
 *  table:                                                   * 
 *     1 => char                                             *
 *     2 => int                                              *
 *     3 => long long int                                    *
 *     4 => float                                            *
 *     5 => double                                           *
 *************************************************************/

#define MAX 200

/* Kutuphanelerin tanitilmasi */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Prototipler */
int hwDecode(const char filenme[], int arr_out[]);
double getFieldValue(int *currentPositionOnBuffer, int *numberOfFields, int fieldType, unsigned char *buffer);
int getFieldLengthInBytes(int fieldType);


int main(){
    int arr[10000];
    hwDecode("elif.dat",arr);
    return 1;
}


/* Gonderilen alanin türüne gore byte cinsinden veri alaninin boyunu dondurur. */
int getFieldLengthInBytes(int fieldType)
{
  int fieldLengthInBytes;

  if (fieldType == 1)                  
    fieldLengthInBytes = 1; /* Char == 1 byte */
  
  else if (fieldType == 2 || fieldType == 4) 
    fieldLengthInBytes = 4; /* Int ve Float == 4 byte */
  
  else if (fieldType == 3 || fieldType == 5) 
    fieldLengthInBytes = 8; /* Long long int ve Double == 8 byte */
  
  else    
      fieldLengthInBytes = 0; /* Orada deger yoksa  */
    
    return (fieldLengthInBytes);
}

/*************************************************************************************************
 * Inputs:                                                                                       *
 * -*buffer: 1 kayidin tamamini tutan karakter dizisidir.                                        *
 * -*currentPositionOnBuffer: Veri alaninin buffer uzerindeki baslangic noktasini tutar.         *
 * - digit: Veri alaninin veri tipidir.(1:Char, 2:Int, 3:Long Long Int, 4:float, 5:Double, 6:bos)*
 * -*numberOfFields: Bir kayittaki veri alani sayisidir.                                         *
 *                                                                                               *
 * -Return value-> Gonderilen veri alani turune gore bulunan sayisal degeri geri dondurur.       *
 *  Alan kullanilmiyor ise 0 doner.                                                              *
 * -*currentPositionOnBuffer: Bir sonraki alani gosterecek sekilde guncellenir.                  *
 * -*numberOfFields: gonderilen veri alani 6 disinde bir deger ise veri alani                    *
 *  sayisini 1 artirilarak guncellenir.                                                          *
 ************************************************************************************************/
double getFieldValue(int *currentPositionOnBuffer, int *numberOfFields, int fieldType, unsigned char *buffer)
{
  int fieldLengthInBytes, i, retValI;
  double retValD;
  float retValF;
  long long int retValLL;
  unsigned char retValC;
  unsigned char tmpBuffer[8]="";
    
  retValI = 0;
  retValD = 0;
  retValF = 0;
  retValLL = 0;
  retValC = '\0';

  /* Eger veri alani veri turu 6 ise bu veri alaninin yer almadigi anlamina gelmektedir. */
  if (fieldType == 6) 
    return (0);
    
  fieldLengthInBytes = getFieldLengthInBytes(fieldType);
  *numberOfFields = *numberOfFields + 1; /* Degisken sayisini 1 artir.*/

  /* Veri ilgili degiskene donusturulebilmesi icin gecici bir degiskene kopyalanir.*/
  for (i = 0; i < fieldLengthInBytes; i++)
  {
    tmpBuffer[i] = buffer[*currentPositionOnBuffer + i];
  }
    
  if (fieldType == 1) 
    memcpy(&retValC,  tmpBuffer, sizeof(char));
    
  else if (fieldType == 2) 
    memcpy(&retValI,  tmpBuffer, sizeof(int));
    
  else if (fieldType == 3) 
    memcpy(&retValLL, tmpBuffer, sizeof(long long int));
  
  else if (fieldType == 4) 
    memcpy(&retValF,  tmpBuffer, sizeof(float));
  
  else if (fieldType == 5) 
    memcpy(&retValD,  tmpBuffer, sizeof(double));

  *currentPositionOnBuffer = *currentPositionOnBuffer + fieldLengthInBytes;
  retValD = retValD + retValC + retValF+retValI + retValLL;
  
  return (retValD);
}

int hwDecode(const char filename[], int arr_out[])
{
  FILE *filePointer;
  double runningRowSum, calculatedAverage, averageOnFile;
  int d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, i, found;
  int currentPositionOnBuffer, numberOfFields, fileSize, runningRowSize, averageRowSizeOnFile;
  unsigned char buffer[MAX]="";/* Turunu bilmedigimiz icin ornek olarak char okuruz. */
  found = 0; /* Flag */

  filePointer = fopen(filename, "rb+"); /* Dosya acilir.*/
  if (filePointer == NULL) 
  {
    printf("Dosya acilamadi\n");
    fclose(filePointer);
  	return (-1);
  }
  
  fseek(filePointer, 0, SEEK_END); /* Dosyanin  sonuna gider. */
  /* ftell fonksiyonu bulundugun yerin kacinci byte oldugunu soyler bu deger dosyanin boyutunu verir.*/    
  fileSize = ftell(filePointer); 
  averageRowSizeOnFile = fileSize / 1000; /* Ortalama kayit boyunu verir.*/
  rewind(filePointer); /* Dosyanin basina geri gelir.*/
  fread(buffer, 1, averageRowSizeOnFile, filePointer); /* Bir kayit okur ve bunu buffer a atar.*/
  fclose(filePointer); /* Acilan dosya kapatilir */
  /* En sonda mutlaka double olmali bu nedenle ortalama kayit boyunu 8 byte indirilir.*/    
  averageRowSizeOnFile = averageRowSizeOnFile - 8; 

/****************************************************************************************
 * Ortalama haric en fazla 10 degisken olabilir. Asagidaki dongulerde butun olasiliklar *
 * olusturularak, ortaya cikan kombinasyonun istenen ortalama kayit boyuna sahip olup   *
 * olmadigi, eger ortalama kayit boyu uygunsa; ortalama degerin dosyadaki ortalama      *
 * degere esit olup olmadigi kontrol edilir.Indis degiskenlerinin degerleri asagidaki   *
 * durumlari ifade etmektedir. Ornek:                                                   *
 *     1 => char                                                                        *
 *     2 => int                                                                         *
 *     3 => long long int                                                               *
 *     4 => float                                                                       *
 *     5 => double                                                                      *
 *     6 => degisken tanimli degil.                                                     *
 ****************************************************************************************/
  for (d1 = 1; d1 < 7 && found == 0; d1++)
  {
    runningRowSize = getFieldLengthInBytes(d1);
    for (d2 = 1; d2 < 7 && found == 0; d2++)
    {
      runningRowSize = runningRowSize + getFieldLengthInBytes(d2);
      for (d3 = 1; d3 < 7 && found == 0; d3++)
      {
        runningRowSize = runningRowSize + getFieldLengthInBytes(d3);
        for (d4 = 1; d4 < 7 && found == 0; d4++)
        {
          runningRowSize = runningRowSize + getFieldLengthInBytes(d4);
          for (d5 = 1; d5 < 7 && found == 0; d5++)
          {
            runningRowSize = runningRowSize + getFieldLengthInBytes(d5);
            for (d6 = 1; d6 < 7 && found == 0; d6++)
            {
              runningRowSize = runningRowSize + getFieldLengthInBytes(d6);
              for (d7 = 1; d7 < 7 && found == 0; d7++)
              {
                runningRowSize = runningRowSize + getFieldLengthInBytes(d7);
                for (d8 = 1; d8 < 7 && found == 0; d8++)
                {
                  runningRowSize = runningRowSize + getFieldLengthInBytes(d8);
                  for (d9 = 1; d9 < 7 && found == 0; d9++)
                  {
                    runningRowSize = runningRowSize + getFieldLengthInBytes(d9);
                    for (d10 = 1; d10 < 7 && found == 0; d10++) 
                    {
                      /* Secilen kombinasyondaki kayit boyu istenen kayit boyuna uyuyor mu kontrolu. */
                      if ((runningRowSize + getFieldLengthInBytes(d10)) == averageRowSizeOnFile)
                      {  
                        /* Dosyadan buldugumuz boyla karsilastirir. */
                        currentPositionOnBuffer = 0; /* Buffer'da bulunulan pozisyon */
                        numberOfFields = 0; /* Bir kayittaki degisken sayisi.*/
                        /* Ortalama hesaplamak için her bir elemanin degeri ayri ayri bulunarak toplama eklenir. */
                        runningRowSum = getFieldValue(&currentPositionOnBuffer,&numberOfFields,d1,buffer);
                        runningRowSum = runningRowSum + getFieldValue(&currentPositionOnBuffer,&numberOfFields,d2,buffer);
                        runningRowSum = runningRowSum + getFieldValue(&currentPositionOnBuffer,&numberOfFields,d3,buffer);
                        runningRowSum = runningRowSum + getFieldValue(&currentPositionOnBuffer,&numberOfFields,d4,buffer);
                        runningRowSum = runningRowSum + getFieldValue(&currentPositionOnBuffer,&numberOfFields,d5,buffer);
                        runningRowSum = runningRowSum + getFieldValue(&currentPositionOnBuffer,&numberOfFields,d6,buffer);
                        runningRowSum = runningRowSum + getFieldValue(&currentPositionOnBuffer,&numberOfFields,d7,buffer);
                        runningRowSum = runningRowSum + getFieldValue(&currentPositionOnBuffer,&numberOfFields,d8,buffer);
                        runningRowSum = runningRowSum + getFieldValue(&currentPositionOnBuffer,&numberOfFields,d9,buffer);
                        runningRowSum = runningRowSum + getFieldValue(&currentPositionOnBuffer,&numberOfFields,d10,buffer);
                        /* Ortalama degerin hesaplanmasi  */
                        calculatedAverage = runningRowSum / numberOfFields; 
         
                         /* Dosyada yazili olan ortalama degerinin okunmasi. */
                        averageOnFile = getFieldValue(&currentPositionOnBuffer,&numberOfFields, 5,buffer);

                          /* Programda hesaplanan ortalama ile dosyada yazili ortalama ayni ise aranan format bulunmustur.*/
                        if (calculatedAverage == averageOnFile) 
                        {
                          /* Index degerlerinin 6 olmasi o degerin bos oldugunu gösterir.*/
                          arr_out[0] = d1; arr_out[1] = d2; arr_out[2] = d3; arr_out[3] = d4; arr_out[4] = d5;
                          arr_out[5] = d6; arr_out[6] = d7; arr_out[7] = d8; arr_out[8] = d9; arr_out[9] = d10;
                          for (i = 0; i < 10; i++)
                          {
                            if (arr_out[i] == 6)
                            arr_out[i] = -1;
                          	printf("%d*",arr_out[i]);
                          }
                          found = 1; /* Flag */
                        }
                      }
                    }
                   runningRowSize = runningRowSize - getFieldLengthInBytes(d9);
                  }
                  runningRowSize = runningRowSize - getFieldLengthInBytes(d8);
                }
                runningRowSize = runningRowSize - getFieldLengthInBytes(d7);
              }
              runningRowSize = runningRowSize - getFieldLengthInBytes(d6);
            }
            runningRowSize = runningRowSize - getFieldLengthInBytes(d5);
          }
          runningRowSize = runningRowSize - getFieldLengthInBytes(d4);
        }
        runningRowSize = runningRowSize - getFieldLengthInBytes(d3);
      }
      runningRowSize = runningRowSize - getFieldLengthInBytes(d2);
    }
  }
  return (0);
}