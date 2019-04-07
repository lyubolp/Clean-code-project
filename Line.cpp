#include "Line.h"
#include <iostream>

Line::Line() : BaseShape() {}

Line::Line(const point* arrayOfPoints, const std::string lineColor) : BaseShape(arrayOfPoints, 2, lineColor, LineT) {}


point Line::getAdditionalPoints() const { return point(0, 0); };

void Line::setSize(const point size) {}

