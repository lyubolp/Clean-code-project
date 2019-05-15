#include "Headers/Polygon.h"
#include <iostream>




Polygon::Polygon(): BaseShape(){ }
Polygon::Polygon(const point* arrayOfPoints, int amountOfPoints, const std::string lineColor) : BaseShape(arrayOfPoints, amountOfPoints,lineColor, POLYGON) {}

void Polygon::print() const
{
    point* pointsOfTheShapeToPrint; //We get the points of the current object
    pointsOfTheShapeToPrint = BaseShape::getPoints(); //Get the points

    std::cout << "polygon ";
    int pointsCountOfTheShapeToPrint = BaseShape::getPointsCount();

    for (int i = 0; i < pointsCountOfTheShapeToPrint; i++) //The polygon has an unknown amount of points
    {
        std::cout << pointsOfTheShapeToPrint[i] << " ";
    }
    std::cout << BaseShape::getColor() << "\n";
}