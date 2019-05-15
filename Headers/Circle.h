
#ifndef CLEAN_CODE_PROJECT_CIRCLE_H
#define CLEAN_CODE_PROJECT_CIRCLE_H

#include "Headers/Base.h"
#include "Headers/Polygon.h"
#include "Headers/Line.h"

#include "Headers/InputValidation.h"
#include "Headers/MathFunctions.h"

class Circle: public BaseShape
{
private:
	double radius;
public:
	Circle();
	Circle(const point*, const std::string, double);

    void setSize(const point) override;
    void print() const override;


    //May be cut down
    /*const bool checkIfPointIsWithinCircle(const point&) const;
    bool checkIfRectangleIsWithinCircle(const Rectangle &) const;
    bool checkIfCircleIsWithinCircle(const Circle&) const;
    bool checkIfLineIsWithinCircle(const Line&) const;
    bool checkIfPolygonIsWithinCircle(const Polygon&) const;*/

    const point getAdditionalPoints() const override;


};

#endif
