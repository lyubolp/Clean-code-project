#include "Rectangle.h"
#include <iostream>
#include "InputValidation.cpp"

Rectangle::Rectangle(): BaseShape() {}
Rectangle::Rectangle(const point* arrayOfPoints, const std::string  shapeColor , const double rectangleWidth, const double rectangleHeight) : BaseShape(arrayOfPoints, 1,shapeColor, RectangleT ), width(rectangleWidth), height(rectangleHeight) 
{
	if (!isNumberBiggerThanZero(width))
	{
		std::cout << "Width is negative. Setting it to 1";
		width = 1;
	}

	if (!isNumberBiggerThanZero(height))
	{
		std::cout << "Height is negative. Setting it to 1";
		height = 1;
	}

}

point Rectangle::getAdditionalPoints() const
{
	return point(width, height);
}

void Rectangle::setSize(const point size)
{
	width = size.x;
	height = size.y;
}
