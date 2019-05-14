#include "Headers/Line.h"
#include <iostream>

Line::Line() : BaseShape() {}

Line::Line(const point* arrayOfPoints, const std::string lineColor) : BaseShape(arrayOfPoints, 2, lineColor, LineT) {}


point Line::getAdditionalPoints() const 
{
	return point(0, 0); 
};

void Line::setSize(const point size) {}

void Line::print() const
{
    point* pointsOfTheShapeToPrint; //We get the points of the current object
    pointsOfTheShapeToPrint = BaseShape::getPoints(); //Get the points

    std::cout << "line " << pointsOfTheShapeToPrint[0] << " " << pointsOfTheShapeToPrint[1] << " " << BaseShape::getColor() << "\n";

}