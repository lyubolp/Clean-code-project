
#ifndef CLEAN_CODE_PROJECT_CIRCLE_HPP
#define CLEAN_CODE_PROJECT_CIRCLE_HPP

#include "Headers/Base.hpp"
#include "Headers/Polygon.hpp"
#include "Headers/Line.hpp"

#include "Headers/InputValidation.hpp"
#include "Headers/MathFunctions.hpp"

class Circle: public BaseShape
{
public:
    Circle();
    Circle(const point*, const std::string&, const double&);

    void setSize(const point&) override;

    void print() const override;

    const point getAdditionalPoints() const override;

private:
	double radius;
};

#endif
