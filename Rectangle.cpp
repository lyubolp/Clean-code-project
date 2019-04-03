#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(): Base() {}
Rectangle::Rectangle(const point* rhs, const std::string  c , const double w, const double h) : Base(rhs, 1,c, RectangleT ), width(w), height(h) {}

point Rectangle::getAdditionalPoints() const
{
	return point(width, height);
}

void Rectangle::setSize(const point p)
{
	width = p.x;
	height = p.y;
}
