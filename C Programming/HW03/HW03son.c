/******************************************************************
 * HW03 Elif Seyma Armagan 151044042                              *
 * ______________________________________	                      *
 * HW03                                                           *
 * Student Name: Elif Seyma ARMAGAN                               *
 * Student ID  : 151044042                                        * 
 * Date        : 04/03/2016                                       *
 * ______________________________________                         *
 * Description:                                                   *
 * -This program checks the given number from user is an odd, a   *
 * factorial or a narcissistic number.                            *
 *             		                                              *  
 *****************************************************************/

/* Kutuphanelerin tanitilmasi */
#include <stdio.h>
#include <math.h>

/* Prototiplerinin tanitilmasi */
int findOddFunction(int number);
int findFactorialFunction(int number);
int choiceMenu();
int continueFunction();
int getNumber();
int findNarcissisticFunction(int number);

int main()
{
	/************************************************************************
	*		                     Start of Main                              *
	* -Main fonksiyonu temel olarak kullanicinin secimine gore istenilen    *
	*  fonksiyonu calistirir 										        *
	*                                                                       *
	*************************************************************************/
	   
	/* Degiskenlerin tanitilmasi */
	int userChoice1, number, temp;
	userChoice1=0;
	
printf("\n***************************************************\n");
printf("*                 WELCOME!                        *\n");
printf("* This program checks whether the given number    *\n");
printf("*is an odd, a factorial or a narcissistic number  *\n");
printf("*                                                 *\n");
printf("***************************************************\n");

	while (1) /* Sonsuz Dongu */
	{
		/* Kullanicidan sayiyi alir */
		number = getNumber(); 
		
		/* Eger kullanici yanlis secim yaparsa continueFunciton cagirilir */
		while (number <= 0)   
		{
			temp = continueFunction();
			if (temp == 1) /* Eger y girilmisse */
				number = getNumber();/* Tekrar sayi alir */
			else if (temp == 0) /* Eger n girilmisse */
				return (0); /* Programdan cikar */
		}
		
		/**/
		userChoice1=choiceMenu();
		
		/* Secime gore fonksiyonu cagirir */
		if (userChoice1==1)
			findOddFunction(number);
		else if(userChoice1==2)
			findFactorialFunction(number);
		else if (userChoice1==3)
			findNarcissisticFunction(number);
		else if (userChoice1==4)
			return(0);
		
		/* Devam etmek istedigini sorar */
		if (continueFunction() == 0)
			return (0);
	}
	
	return (0);
	
	/* End of Main */
}

/********************************************************************
*-Bu fonksiyon kullaniciya bir secim menusu sunar.                  *
* Kullanicidan bir secim sayiyi alir ve aldigi bu sayiyi dondurur.  *
********************************************************************/
int choiceMenu()
{
	/* Degiskenlerin tanitilmasi */
	int choice;
		
	printf("Which property would you like to check?\n");
	printf("1)Odd number\n");
	printf("2)Factorial number\n");
	printf("3)Narcissistic number\n");
	printf("Please enter(1/2/3): ");
	scanf("%d",&choice); /* Secimin kullanicidan alinmasi */
	
	return (choice); /* Secimin dondurulmesi */
}

/*********************************************************************
*-Bu fonksiyon uzerinde islem yapilacak integer sayinin kullanicidan *
* alinmasini saglar.Ve alinan bu sayiyi dondurur.                    *
**********************************************************************/
int getNumber()
{
	/* Degiskenlerin tanitilmasi */
	int number = -1;
	
	printf("\nPlease enter a positive integer : ");
	/* Uzerinde islem yapilacak sayinin kullanicidan alinmasi */
	scanf("%d",&number); 
	/* Alinan sayinin integer olmasi gerekir */
	if (number<=0)
		printf("The entered number is not positive.\n");
	
	return (number); /* Alinan integer sayinin dondurulmesi */
}

/********************************************************************
*-Bu fonksiyon kullanicinin yeni bir isleme devam edip etmeyecegini *
* belirlemesini saglar.                                             *
********************************************************************/  
int continueFunction()
{
	/* Degiskenlerin tanitilmasi */
	char userchoice;
	
	printf("Do you want to continue (y/n)? ");
	/* Devam edip etmeyecegi sonucunun kullanicidan alinmasi */
	scanf(" %c" , &userchoice);
	
	if (userchoice=='y' || userchoice=='Y')/* Eger y girilirse 1 dondurur */	
		return (1); 
	/* Eger n girilmisse 0 dondurur ve programi kapatir */
	else if(userchoice=='n' || userchoice=='N')
	{
		printf("Good bye !\n\n");
		return (0);
	}
				
	return (0);
}

/*****************************************************************
* Bu fonksiyon alinan sayinin tek sayi olup olmadigini hesaplar. *
******************************************************************/
int findOddFunction(int number)
{
	/* Bir sayinin 2 ile bolumunden kalan 0 degilse sayi tek sayidir */
	if((number%2)!=0)
		printf("%d is a odd number !\n",number);
	else 	
		printf("%d is not a odd number !\n",number);
		
	return (0);
}

/********************************************************************
* -Bu fonksiyon temelde kullanici tarafindan girilen sayinin        *
*  faktoriyel bir sayi olup olmadigini kontrol eder.                *
*********************************************************************/
int findFactorialFunction(int number)
{
	int i,kalan; /* Degiskenlerin tanitilmasi */

	/* Sayiyi bolmeye 2 den baslar.1 in bir sayiya bolumu sayinin kendisidir */
	i=2;
	/* Sayinin degerini tutarak degiskene atar islemleri degisken ile yapar */
	kalan=number;
	
	if (number==1)/* 1 ozel sayidir ve faktoriyel sayidir. */
	{
		printf("%d is a factorial number !\n",number);
		return (0);
	}


	while(kalan>i)
	{
		/* Sayinin i sayisi ile bolumunden kalan 0 degilse donguden cikar */
		if(kalan % i !=0)
			return (0);
  		/* Sayiyi artirdigimiz sayiya boler ve bu sayiyi surekli 1 artirir*/		
		else
		{
			kalan = kalan / i;
			i=i+1;
		}
	}

	if (kalan==i)
		printf("%d is a factorial number !\n",number);
	else
		printf("%d is not a factorial number\n", number);

	return (0);
}

/********************************************************************
* -Bu fonksiyon temelde kullanici tarafindan girilen sayinin        *
*  narsist bir sayi olup olmadigini kontrol eder.                   *
*********************************************************************/
int findNarcissisticFunction(int number)
{
	/* Degiskenlerin tanitilmasi */
	int digit,toplam,lastdigit,number1; 
	digit=0;
	/* Sayinin degerinin degismemesi icin degiskene atanmasi */
	number1=number;

	/* Sayinin basamak sayisinin bulunmasi */
 	while(number1>0)
 	{
		/* Sayi 0 dan buyuk oldugu surece 10 a boler basamak sayisini artirir.*/
	  	number1 = number1 / 10;
	  	digit++;
 	}
	
	/* Sayinin degerinin degismemesi icin degiskene atar. */
	number1=number;
	toplam=0;
 	
 	/* Sayimiz 0 a esit olmadigi surece donguye girer. */	
 	while (number1!=0)
 	{
 		/* Sayimiz 10 dan buyukse son basamak 10 a bolumunden kalandir. */	
 		if (number1>=10)
 			lastdigit = number1%10;
 		else 
 			lastdigit = number1;
		
 		toplam = toplam + pow(lastdigit,digit);
 		number1 = number1 / 10;
 	}
		/* Eger buldugumuz toplam, sayimiza esitse narsist sayidir. */
		if (toplam==number)
			printf("%d is narcissistic number!\n",number);
		else
			printf("%d is not a narcissistic number!\n",number);
	
	return (0);

}

/*****************************************************************************
 * 			      Elif Seyma Armagan 151044042  End of HW03         		 *
 *****************************************************************************/
