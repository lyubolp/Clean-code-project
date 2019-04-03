#include "Polygon.h"
#include <iostream>




Polygon::Polygon(): BaseShape(){ }
Polygon::Polygon(const point* rhs, int pc, const std::string c) : BaseShape(rhs, pc,c, PolygonT) {}

point Polygon::getAdditionalPoints() const { return point(0, 0); }

void Polygon::setSize(const point p) {}
