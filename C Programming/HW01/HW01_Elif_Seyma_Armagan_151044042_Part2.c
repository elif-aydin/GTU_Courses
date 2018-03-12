/************************************************************************
 * HW01_Elif_Seyma_Armagan_151044042_Part2.c                            *
 * ______________________________________	                            *
 * HW01 Part2                                                           *
 * Student Name: Elif Seyma ARMAGAN                                     *
 * Student ID  : 151044042                                              * 
 * Date        : 18/02/2016                                             *
 * ______________________________________                               *
 * Aciklama:                                                            *
 * -Kullanicin girdigi dogum tarihine gore o gunku yasinin hesaplanmasi *
 * -Kullanicin alinan verilere gore baska bir gezegendeki               *
 *  yasam suresinin hesaplanmasi                                        *	 
 ************************************************************************/

/*Kutuphanelerin tanitimi*/
#include <stdio.h>

int main()
{	
	/*Degiskenlerin tanitilmasi*/
	int currentYear,currentMonth,currentDay;
	int birthdateYear,birthdateMonth,birthdateDay,pastDays;
	int yourDay,yourMonth,yourYear;
	int planetDay,planetMonth,planetYear;
	
    /*Simdiki tarihin alinmasi*/
	printf("Please enter the current date.\n");
	printf("Year: ");
	scanf ("%d",&currentYear);
	printf("Month: ");
	scanf ("%d",&currentMonth);
	printf("Day: ");
	scanf ("%d",&currentDay);

    /*Dogum tarihinin alinmasi*/
	printf("Please enter your birthdate.\n");
	printf("Year: ");
	scanf ("%d",&birthdateYear);
	printf("Month: ");
	scanf ("%d",&birthdateMonth);
	printf("Day: ");
	scanf ("%d",&birthdateDay);
	
	/*Dunyada kac gun yasadiginin hesaplanmasi  */
	pastDays=(365-(((birthdateMonth-1)*30)+birthdateDay))+
	((currentYear-(birthdateYear+1))*365)+((currentMonth-1)*30)+currentDay;
	
	/*Dunyada kac gun yasadiginin gosterilmesi*/
	printf ("You have lived %d days\n",pastDays);

	/*Baska bir gezegene gore degerlerin alinmasi*/
	printf("Please enter about the time of another planet: \n");
	printf("How many hours is a day? ");
	scanf ("%d",&planetDay);
	printf("How many days is a month? ");
	scanf ("%d",&planetMonth);
	printf("How many months is a year? ");
	scanf ("%d",&planetYear);

	/*Baska bir gezegendeki gun ay ve yilin kesaplanmasi*/	
	yourYear=(int)((pastDays)*(int)(24/planetDay)/(planetMonth*planetYear));
	yourMonth=(int)((pastDays*24/planetDay)-(yourYear*planetMonth*planetYear))/(planetMonth);
	yourDay=(int)((pastDays)*(int)(24/planetDay)-(yourYear*planetMonth*planetYear))-(planetMonth*(int)yourMonth);
	
	/*Degerleri alinan gezegende kac yildir yasandiginin gosterilmesi*/
	printf 
	("If you lived in a planet where a day is %d hours, a month is %d days and a year is %d months: you were %d years, %d months and %d days old.\n",planetDay,planetMonth,planetYear,yourYear,yourMonth,yourDay);

	return 0;
}

