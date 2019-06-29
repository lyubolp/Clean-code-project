#include "Headers/Line.hpp"
#include <iostream>

Line::Line() : BaseShape() {}

Line::Line(const Point* arrayOfPoints, const std::string lineColor) : BaseShape({arrayOfPoints, 2}, lineColor, LINE) {}

void Line::print() const
{
    const Point* pointsOfTheShapeToPrint;
    pointsOfTheShapeToPrint = BaseShape::getPoints();

    std::cout << "line " << pointsOfTheShapeToPrint[0] << " " << pointsOfTheShapeToPrint[1] << " " << BaseShape::getColor() << "\n";

}

const Point Line::getAdditionalPoints() const
{
	return Point(0, 0);
};

void Line::setSize(const Point& size)
{

}

