#ifndef CLEAN_CODE_PROJECT_RECTANGLE_HPP
#define CLEAN_CODE_PROJECT_RECTANGLE_HPP

#include "Headers/Base.hpp"
#include "Headers/Polygon.hpp"
#include "Headers/Line.hpp"
#include "Headers/Circle.hpp"

#include "Headers/InputValidation.hpp"
#include "Headers/MathFunctions.hpp"

class Rectangle: public BaseShape
{
public:
	Rectangle();
	Rectangle(const Rectangle&);
	Rectangle(const point*, const std::string, const double, const double);
	Rectangle&operator=(const Rectangle&);
	
	const point getAdditionalPoints() const override;
	void setSize(const point&) override;

    void print() const override;

private:
    double width;
    double height;

};

#endif