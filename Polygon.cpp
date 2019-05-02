#include "Polygon.h"
#include <iostream>




Polygon::Polygon(): BaseShape(){ }
Polygon::Polygon(const point* arrayOfPoints, int amountOfPoints, const std::string lineColor) : BaseShape(arrayOfPoints, amountOfPoints,lineColor, PolygonT) {}

point Polygon::getAdditionalPoints() const 
{
	return point(0, 0); 
}

void Polygon::setSize(const point size) {}
