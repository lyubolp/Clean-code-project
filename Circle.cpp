#include "Circle.h"
#include <iostream>
Circle::Circle() : BaseShape() {}
Circle::Circle(const point* rhs, const std::string c, double r) : BaseShape(rhs, 1, c, CircleT), radius(r) {}

point Circle::getAdditionalPoints() const
{
	return point(radius, 0);
}

void Circle::setSize(const point p)
{
	radius = p.x;
}
