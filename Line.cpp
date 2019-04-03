#include "Line.h"
#include <iostream>

Line::Line() : Base() {}

Line::Line(const point* rhs, const std::string c) : Base(rhs, 2, c, LineT) {}


point Line::getAdditionalPoints() const { return point(0, 0); };

void Line::setSize(const point p) {}

