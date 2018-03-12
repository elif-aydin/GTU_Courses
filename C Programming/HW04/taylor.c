#include <stdio.h>
#define PI 3.14

double cosine(int degree, int n);
double sine(int degree, int n);
double pow(double degree, double n);
double factorial(int number);
void getInputs(int* degree, int* n);


int main()
{
	int degree;
	int n;

	getInputs(&degree,&n);
	

return 0;
}

void getInputs(int* degree, int* n)
{  
	scanf("%d",degree);
	scanf("%d",n);
   
	printf ("sin(%d) where n is %d = %.4f\n",*degree,*n,sine(*degree,*n));
	printf ("cos(%d) where n is %d = %.4f\n",*degree,*n,cosine(*degree,*n));
		
}

double cosine(int degree, int n)

{
	int k;
	double radValue, result;

	radValue = (degree * PI)/(180);
	result=0;
	for(k=0; k<n; k++)
		result = result + ((pow(-1,k) * pow(radValue,2*k)) / factorial(2*k)); 
		
		return (result);
}


double sine(int degree, int n)
{
	int k;
    double radValue ,result;

    radValue = (degree * PI)/(180);
	result=0;
	for (k=0; k<n; k++)
	   result = result + ((pow(-1,k) * pow(radValue,2*k+1)) / factorial(2*k+1));

	return (result);

}
/* Bir sayinin kuvvetini hesaplayan fonksiyon */
double pow(double degree, double n)

{
    double value = 1.0;
    int i;
    
    if (n==0)
    	return (1);

    for (i=1; i<=n; i++)
        value = value * degree;
    
    return (value);
}

/* Bir sayinin faktoriyelini hesaplayan fonksiyon */
double factorial(int number)
{
	double result,i;
	result=1;

	if (number==0 || number==1)
		return (1);

	for(i=1; i<=number; i++)
		result = result * i;
		return (result);

}
