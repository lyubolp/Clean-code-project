//
// Created by lyubo on 29.06.19.
//

#include "Headers/Point.hpp"


Point::Point() = default;
Point::Point(const double& a, const double& b) :x(a), y(b)
{
    if (x < 0)
    {
        std::cout << "X is less than 0, setting it to 0. \n";
        x = 0;
    }
    if (y < 0)
    {
        std::cout << "Y is less than 0, setting it to 0. \n";
        y = 0;
    }
}

double Point::getX() const
{
    return x;
}
double Point::getY() const
{
    return y;
}

void Point::setX(const double& newX)
{
    if(newX >= 0)
    {
        x = newX;
    }
    else
    {
        std::cout << "X is less than 0, setting it to 0. \n";
        x = 0;
    }
}

void Point::setY(const double& newY)
{
    if(newY >= 0)
    {
        y = newY;
    }
    else
    {
        std::cout << "Y is less than 0, setting it to 0. \n";
        y = 0;
    }
}
