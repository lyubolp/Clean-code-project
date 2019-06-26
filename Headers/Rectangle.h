#ifndef CLEAN_CODE_PROJECT_RECTANGLE_H
#define CLEAN_CODE_PROJECT_RECTANGLE_H

#include "Headers/Base.h"
#include "Headers/Polygon.h"
#include "Headers/Line.h"
#include "Headers/Circle.h"

#include "Headers/InputValidation.h"
#include "Headers/MathFunctions.h"

class Rectangle: public BaseShape
{
private:
	double width;
	double height;
public:
	Rectangle();
	Rectangle(const Rectangle&);
	Rectangle(const point*, const std::string, const double, const double);
	Rectangle&operator=(const Rectangle&);
	
	const point getAdditionalPoints() const override;
	void setSize(const point) override;

    void print() const override;

    bool checkIfPointIsWithinRectangle(const point &) const;
    bool checkIfRectangleIsWithinRectangle(const Rectangle &) const;
    bool checkIfCircleIsWithinRectangle(const Circle &) const;
    bool checkIfLineIsWithinRectangle(const Line &) const;
    bool checkIfPolygonIsWithinRectangle(const Polygon &) const;
};

#endif