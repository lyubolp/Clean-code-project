#include "Headers/Circle.hpp"
#include <iostream>

Circle::Circle() : BaseShape(), radius(0) {}
Circle::Circle(const Point* arrayOfPoints, const std::string& shapeColor, const double& circleRadius) : BaseShape({arrayOfPoints, 1}, shapeColor, CIRCLE), radius(circleRadius) {
    if (!isNumberBiggerThanZero(radius)) {
        std::cout << "Radius is negative... setting it to 1";
        radius = 1;
    }
}
void Circle::setSize(const Point& circleRadius)
{
	if (isNumberBiggerThanZero(radius))
	{
		radius = circleRadius.x;
	}
	else
	{
		throw std::invalid_argument("Radius is negative");
	}
}

void Circle::print() const
{
    std::cout << "circle " << *getPoints() << " " << getAdditionalPoints().x << " " << getColor() << "\n";
}

const Point Circle::getAdditionalPoints() const
{
    return Point(radius, 0);
}
