#include "Circle.h"
#include <iostream>
Circle::Circle() : BaseShape() {}
Circle::Circle(const point* arrayOfPoints, const std::string shapeColor, double circleRadius) : BaseShape(arrayOfPoints, 1, shapeColor, CircleT), radius(circleRadius) {}

point Circle::getAdditionalPoints() const
{
	return point(radius, 0);
}

void Circle::setSize(const point circleRadius)
{
	radius = circleRadius.x;
}
