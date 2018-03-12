#include <stdio.h>
#define pi 3


int areaOfRectangle(int rectangleWidth, int rectangleHeight);
int perimeterOfRectangle(int rectangleWidth, int rectangleHeight);
int areaOfSquare(int squareWidth);
int perimeterOfSquare(int squareWidth);
int areaOfCircle(int radius);
int perimeterOfCircle(int radius);




int main()

{
int rectangleWidth,rectangleHeight,squareWidth,circleRadius;

	printf("Please enter the width of the rectangle:");
	scanf("%d",&rectangleWidth);

	printf("Please enter the height of the rectangle:");
	scanf("%d",&rectangleHeight);

	printf("The area of the rectangle is: %d\n",
	areaOfRectangle(rectangleWidth,rectangleHeight));

	printf("The perimeter of the rectangle is: %d\n",
	perimeterOfRectangle(rectangleWidth,rectangleHeight));
	


	printf("Please enter the width of the square:");
	scanf("%d",&squareWidth);
	printf("The area of the square is: %d\n",areaOfSquare(squareWidth));
	printf("The perimeter of the square is: %d\n",
	perimeterOfSquare(squareWidth));


	printf("Please enter the radius of the circle:");
	scanf("%d",&circleRadius);
	printf("The area of the circle is: %d\n",areaOfCircle(circleRadius));
	printf("The perimeter of the circle is: %d\n",
	perimeterOfCircle(circleRadius));

return 0;
}



int areaOfRectangle(int rectangleWidth, int rectangleHeight)

{
	return(rectangleWidth*rectangleHeight);
}

int perimeterOfRectangle(int rectangleWidth, int rectangleHeight)

{
	return(2*(rectangleHeight+rectangleWidth));
}

int areaOfSquare(int squareWidth)

{
	return(squareWidth*squareWidth);
}

int perimeterOfSquare(int squareWidth)
{
    return(2*(squareWidth+squareWidth));
}

int areaOfCircle(int circleRadius)
{
	return(pi*circleRadius*circleRadius);
}
int perimeterOfCircle(int circleRadius)
{
	return(2*pi*circleRadius);
}
