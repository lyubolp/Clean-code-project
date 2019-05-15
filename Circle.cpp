#include "Headers/Circle.h"
#include <iostream>

Circle::Circle() : BaseShape() {}
Circle::Circle(const point* arrayOfPoints, const std::string shapeColor, double circleRadius) : BaseShape(arrayOfPoints, 1, shapeColor, CIRCLE), radius(circleRadius) {
    if (!isNumberBiggerThanZero(radius)) {
        std::cout << "Radius is negative... setting it to 1";
        radius = 1;
    }
}
const point Circle::getAdditionalPoints() const
{
    std::cout << "Circle called";
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

void Circle::print() const
{
    std::cout << "circle " << BaseShape::getPoints() << radius << BaseShape::getColor() << "\n";
}

/*bool Circle::checkIfPointIsWithinCircle(const point & pointToCheck) const
{
    int radius = this->getAdditionalPoints().x;
    return ((pow((pointToCheck.x - this->getPoints()->x), 2) + pow((pointToCheck.y - this->getPoints()->y), 2)) <= pow(radius, 2));
}

bool Circle::checkIfRectangleIsWithinCircle(const Rectangle & objectToCheck) const
{
    point rectanglePointA = *(objectToCheck.getPoints());
    point rectanglePointB(rectanglePointA.x + objectToCheck.getAdditionalPoints().x, rectanglePointA.y);
    point rectanglePointC(rectanglePointA.x, rectanglePointA.y + objectToCheck.getAdditionalPoints().y);
    point rectanglePointD(rectanglePointA.x + objectToCheck.getAdditionalPoints().x, rectanglePointA.y + objectToCheck.getAdditionalPoints().y);


    return checkIfPointIsWithinCircle(rectanglePointA) && checkIfPointIsWithinCircle(rectanglePointB) && checkIfPointIsWithinCircle(rectanglePointC) && checkIfPointIsWithinCircle(rectanglePointD);
}

bool Circle::checkIfCircleIsWithinCircle(const Circle & objectToCheck) const
{
    double distanceBetweenCenterOfBothCircles = getDistanceBetweenTwoPoints(*this->getPoints(), *objectToCheck.getPoints());

    return ((objectToCheck.getAdditionalPoints().x + distanceBetweenCenterOfBothCircles) < this->getAdditionalPoints().x);
}

bool Circle::checkIfLineIsWithinCircle(const Line & objectToCheck) const
{
    return checkIfPointIsWithinCircle(objectToCheck.getPoints()[0]) && checkIfPointIsWithinCircle(objectToCheck.getPoints()[1]);
}

bool Circle::checkIfPolygonIsWithinCircle(const Polygon &objectToCheck) const
{

    int amountOfPointsInShape = objectToCheck.getPointsCount();

    bool result = true;
    for (int i = 0; i < amountOfPointsInShape; i++)
    {
        if (!checkIfPointIsWithinCircle(objectToCheck.getPoints()[i]))
        {
            result = false;
            return result;
        }
    }
    return result;
}*/