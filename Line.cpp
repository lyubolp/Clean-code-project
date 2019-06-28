#include "Headers/Line.hpp"
#include <iostream>

Line::Line() : BaseShape() {}

Line::Line(const point* arrayOfPoints, const std::string lineColor) : BaseShape({arrayOfPoints, 2}, lineColor, LINE) {}

void Line::print() const
{
    const point* pointsOfTheShapeToPrint;
    pointsOfTheShapeToPrint = BaseShape::getPoints();

    std::cout << "line " << pointsOfTheShapeToPrint[0] << " " << pointsOfTheShapeToPrint[1] << " " << BaseShape::getColor() << "\n";

}

const point Line::getAdditionalPoints() const
{
	return point(0, 0); 
};

void Line::setSize(const point& size)
{

}

