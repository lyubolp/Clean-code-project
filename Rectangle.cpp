#include "Headers/Rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(): BaseShape(), width(0), height(0) {}
Rectangle::Rectangle(const Point* arrayOfPoints, const std::string  shapeColor , const double rectangleWidth, const double rectangleHeight) : BaseShape({arrayOfPoints, 1},shapeColor, RECTANGLE ), width(rectangleWidth), height(rectangleHeight)
{
    bool isWidthLessThanZero = !isNumberBiggerThanZero(width);
	if (isWidthLessThanZero)
	{
		std::cout << "Width is negative. Setting it to 1";
		width = 1;
	}

	bool isHeightLessThanZero = !isNumberBiggerThanZero(height);
	if (isHeightLessThanZero)
	{
		std::cout << "Height is negative. Setting it to 1";
		height = 1;
	}

}
Rectangle::Rectangle(const Rectangle& objectToCopyFrom):BaseShape(objectToCopyFrom),width(objectToCopyFrom.getAdditionalPoints().x), height(objectToCopyFrom.getAdditionalPoints().y)
{

}

Rectangle& Rectangle::operator=(const Rectangle & rhs)
{
    if(this != & rhs)
    {
        BaseShape::operator=(rhs);
        setSize(rhs.getAdditionalPoints());
    }
    return *this;
}

const Point Rectangle::getAdditionalPoints() const
{
	return Point(width, height);
}

void Rectangle::setSize(const Point& size)
{
    if (isNumberBiggerThanZero(size.x))
    {
        width = size.x;
    }
    else
    {
        throw std::invalid_argument("Width is negative\n");
    }

    if (isNumberBiggerThanZero(size.y))
    {
        height = size.y;
    }
    else
    {
        throw std::invalid_argument("Height is negative\n");
    }
}

void Rectangle::print() const
{
    std::cout << "rectangle " << *(getPoints()) << " " << getAdditionalPoints() << " " << BaseShape::getColor() << "\n";
}
