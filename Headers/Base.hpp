#pragma once
#include <iostream>
#include <string>
#include "Point.hpp"

enum shape
{
	RECTANGLE,
	CIRCLE,
	LINE,
	POLYGON,
	DEFAULT
};
std::ostream& operator<<(std::ostream& os, Point p);

class BaseShape
{

public:
    BaseShape();
    BaseShape(const std::pair<const Point*, const int>& ,const std::string&, const shape&);
    BaseShape(const BaseShape&);
    BaseShape& operator=(const BaseShape&);
    virtual ~BaseShape();

    const shape getType() const;

    const std::string getColor() const;

    const Point * getPoints() const;
    const int getPointsCount() const;
    virtual const Point getAdditionalPoints() const = 0;

    void translate(const int&, const int&);
    virtual void print() const = 0;

protected:

    void setAllFields(const std::pair<const Point *, const int>&, const std::string&, const shape&);

    void setTypeOfShape(const shape&);
    void setColor(const std::string&);

    void setPoints(const Point&, const int&); //Sets a Point based on Point number (1-n), where n is the number of points;
    void setPoints(const double&, const double&, const int&);
    void setPoints(const Point*, const int&); //All points

    void setPointCount(const int&);

    virtual void setSize(const Point&) = 0;

private:

    shape shapeType; //Types are triangle, rectangle, circle, line

    std::string color;

    Point * points; //Triangle has 1 Point, Rectangle 1, Circle has 0, Line has 2
    int pointsCount; //Points count


};

