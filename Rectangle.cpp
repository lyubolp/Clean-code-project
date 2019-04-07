#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(): BaseShape() {}
Rectangle::Rectangle(const point* arrayOfPoints, const std::string  shapeColor , const double rectangleWidth, const double rectangleHeight) : BaseShape(arrayOfPoints, 1,shapeColor, RectangleT ), width(rectangleWidth), height(rectangleHeight) {}

point Rectangle::getAdditionalPoints() const
{
	return point(width, height);
}

void Rectangle::setSize(const point size)
{
	width = size.x;
	height = size.y;
}
