#include "Circle.h"
#include <iostream>
Circle::Circle() : Base() {}
Circle::Circle(const point* rhs, const std::string c, double r) : Base(rhs, 1, c, CircleT), radius(r) {}

point Circle::getAdditionalPoints() const
{
	return point(radius, 0);
}

void Circle::setSize(const point p)
{
	radius = p.x;
}
