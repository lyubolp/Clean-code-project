#include "Headers/Rectangle.h"
#include <iostream>

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
Rectangle::Rectangle(const BaseShape& objectToCopyFrom):BaseShape(objectToCopyFrom),width(objectToCopyFrom.getAdditionalPoints().x), height(objectToCopyFrom.getAdditionalPoints().y)
{

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

void Rectangle::print() const
{
    std::cout << "rectangle " << BaseShape::getPoints() << " " << BaseShape::getAdditionalPoints() << " " << BaseShape::getColor() << "\n";
}

bool Rectangle::checkIfPointIsWithinRectangle(const point & pointToCheck) const
{
    double rectangleAX = this->getPoints()->x;
    double rectangleAY = this->getPoints()->y;

    double rectangleBX = rectangleAX + this->getAdditionalPoints().x;
    double rectangleCY = rectangleAY + this->getAdditionalPoints().y;

    return checkIfDoubleIsInInterval(pointToCheck.x, {rectangleAX, rectangleBX}) && checkIfDoubleIsInInterval(pointToCheck.y, {rectangleAY, rectangleCY});
}

bool Rectangle::checkIfRectangleIsWithinRectangle(const Rectangle& objectToCheck) const
{
    point rectangleDiagonalPointA = point(objectToCheck.getPoints()->x, objectToCheck.getPoints()->y);
    point rectangleDiagonalPointB = point(rectangleDiagonalPointA.x + objectToCheck.getAdditionalPoints().x, rectangleDiagonalPointA.y + objectToCheck.getAdditionalPoints().y);

    return checkIfPointIsWithinRectangle(rectangleDiagonalPointA) && checkIfPointIsWithinRectangle(rectangleDiagonalPointB);
}

bool Rectangle::checkIfCircleIsWithinRectangle(const Circle & objectToCheck) const
{
    point centerOfNewRectangle(objectToCheck.getPoints()->x, objectToCheck.getPoints()->y - objectToCheck.getAdditionalPoints().x);
    point widthPointOfNewRectangle(objectToCheck.getPoints()->x + objectToCheck.getAdditionalPoints().x, objectToCheck.getPoints()->y);
    point heightPointOfNewRectangle(objectToCheck.getPoints()->x - objectToCheck.getAdditionalPoints().x, objectToCheck.getPoints()->y);
    Rectangle circleMaxBounds(&centerOfNewRectangle, "#000000", getDistanceBetweenTwoPoints(centerOfNewRectangle, widthPointOfNewRectangle), getDistanceBetweenTwoPoints(centerOfNewRectangle, heightPointOfNewRectangle));

    return checkIfRectangleIsWithinRectangle(circleMaxBounds);
}

bool Rectangle::checkIfLineIsWithinRectangle(const Line & objectToCheck) const
{

    return checkIfPointIsWithinRectangle(objectToCheck.getPoints()[0]) && checkIfPointIsWithinRectangle(objectToCheck.getPoints()[1]);
}

bool Rectangle::checkIfPolygonIsWithinRectangle(const Polygon & objectToCheck) const
{
    int amountOfPointsInShape = objectToCheck.getPointsCount();

    bool result = true;
    for (int i = 0; i < amountOfPointsInShape; i++)
    {
        if (!checkIfPointIsWithinRectangle(objectToCheck.getPoints()[i]))
        {
            result = false;
            return result;
        }
    }

    return result;
}
