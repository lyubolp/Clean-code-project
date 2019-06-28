#include "Headers/Polygon.hpp"
#include <iostream>




Polygon::Polygon(): BaseShape(){ }
Polygon::Polygon(const point* arrayOfPoints, int amountOfPoints, const std::string lineColor) : BaseShape({arrayOfPoints, amountOfPoints},lineColor, POLYGON) {}

void Polygon::print() const
{
    const point* pointsOfTheShapeToPrint;
    pointsOfTheShapeToPrint = BaseShape::getPoints();

    std::cout << "polygon ";
    int pointsCountOfTheShapeToPrint = BaseShape::getPointsCount();

    for (int i = 0; i < pointsCountOfTheShapeToPrint; i++)
    {
        std::cout << pointsOfTheShapeToPrint[i] << " ";
    }
    std::cout << BaseShape::getColor() << "\n";
}