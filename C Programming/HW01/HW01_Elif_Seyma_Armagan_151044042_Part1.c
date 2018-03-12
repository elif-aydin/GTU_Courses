/*****************************************************************
 * HW01_Elif_Seyma_Armagan_151044042_part1                       *
 * ______________________________________	                     *
 * HW01 Part1                                                    *
 * Student Name: Elif Seyma ARMAGAN                              *
 * Student ID  : 151044042                                       * 
 * Date        : 18/02/2016                                      *
 * ______________________________________                        *
 * Aciklama:                                                     *
 * Kullanicidan alinan yuzdelere gore final notunun hesaplanmasi *                                           		 
 *****************************************************************/

/*Kutuphanelerin tanitimi*/
#include <stdio.h>

int main()
{
	/*Degiskenlerin tanitilması*/
	float firstMidtermWeight,firstMidtermGrade,secondMidtermWeight,secondMidtermGrade,thirdMidtermWeight,thirdMidtermGrade;
	float firstHomeworkWeight,firstHomeworkGrade,secondHomeworkWeight,secondHomeworkGrade;
	float finalExamWeight,finalExamGrade;
	float finalGrade;

	/*Degiskenlerin kullanicidan alinmasi */
	printf ("Please enter the 1. midterm weight: "); 
	scanf ("%f",&firstMidtermWeight);
	printf ("Please enter the 2. midterm weight: ");
	scanf ("%f",&secondMidtermWeight);
	printf ("Please enter the 3. midterm weight: ");
	scanf ("%f",&thirdMidtermWeight);
	printf ("Please enter the 1. homework weight: ");
	scanf ("%f",&firstHomeworkWeight);
	printf ("Please enter the 2. homework weight: ");
	scanf ("%f",&secondHomeworkWeight);
	printf ("Please enter the final exam weight: ");
	scanf ("%f",&finalExamWeight);
	printf ("Please enter the 1. midterm grade: ");
	scanf ("%f",&firstMidtermGrade);
	printf ("Please enter the 2. midterm grade: ");
	scanf ("%f",&secondMidtermGrade);
	printf ("Please enter the 3. midterm grade: ");
	scanf ("%f",&thirdMidtermGrade);
	printf ("Please enter the 1. homework grade: ");
	scanf ("%f",&firstHomeworkGrade);
	printf ("Please enter the 2. homework grade: ");
	scanf ("%f",&secondHomeworkGrade);
	printf ("Please enter the final exam grade: ");
	scanf ("%f",&finalExamGrade);

	/*Final notunun hesaplanmasi*/
	finalGrade=(firstMidtermWeight*firstMidtermGrade/100)+(secondMidtermWeight*secondMidtermGrade/100)+
	(thirdMidtermGrade*thirdMidtermWeight/100)+(firstHomeworkWeight*firstHomeworkGrade/100)+
	(secondHomeworkWeight*secondHomeworkGrade/100)+(finalExamWeight*finalExamGrade/100);

	/*Final notunun kullaniciya gosterilmesi*/
	printf("Your final grade is: %.2f\n",finalGrade);

	return 0;
}

