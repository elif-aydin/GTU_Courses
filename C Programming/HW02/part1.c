#include <stdio.h>


void calculateLastGrade();

int main(void)
{
	calculateLastGrade();
	calculateLastGrade();
	calculateLastGrade();

	return 0;
}



void calculateLastGrade()
{
	double firstMidtermWeight,firstMidtermGrade;
	double firstHomeworkWeight,firstHomeworkGrade;
	double finalExamWeight,finalExamGrade;
	double finalGrade;
	
	
	printf ("Please enter the 1. midterm weight:");
	scanf("%lf",&firstMidtermWeight);
	printf("Please enter the 1. homework weight:");
	scanf("%lf",&firstHomeworkWeight);
	printf("Please enter the final exam weight:");
	scanf("%lf",&finalExamWeight);
	printf("Please enter the 1. midterm grade:");
	scanf("%lf",&firstMidtermGrade);
	printf("Please enter the 1. homework grade:");
	scanf("%lf",&firstHomeworkGrade);
	printf("Please enter the final exam grade:");
	scanf("%lf",&finalExamGrade);

	finalGrade=((firstMidtermWeight*firstMidtermGrade)/100)
	+((firstHomeworkWeight*firstHomeworkGrade)/100)+
	((finalExamWeight*finalExamGrade)/100);

	printf ("Your final grade is: %f\n",finalGrade);

}
