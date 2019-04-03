#include "Polygon.h"
#include <iostream>




Polygon::Polygon(): Base(){ }
Polygon::Polygon(const point* rhs, int pc, const std::string c) : Base(rhs, pc,c, PolygonT) {}

point Polygon::getAdditionalPoints() const { return point(0, 0); }

void Polygon::setSize(const point p) {}
