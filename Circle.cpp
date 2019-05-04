#include "Circle.h"
#include <iostream>
#include "InputValidation.cpp"
Circle::Circle() : BaseShape() {}
Circle::Circle(const point* arrayOfPoints, const std::string shapeColor, double circleRadius) : BaseShape(arrayOfPoints, 1, shapeColor, CircleT), radius(circleRadius)
{
	if (!isNumberBiggerThanZero(radius))
	{
		std::cout << "Radius is negative... setting it to 1";
		radius = 1;
	}
}

point Circle::getAdditionalPoints() const
{
	return point(radius, 0);
}

void Circle::setSize(const point circleRadius)
{
	if (isNumberBiggerThanZero(radius))
	{
		radius = circleRadius.x;
	}
	else
	{
		std::cout << "Radius is negative. \n";
		return;
	}
	
	
}
