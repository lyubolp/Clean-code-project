
#ifndef CLEAN_CODE_PROJECT_CIRCLE_HPP
#define CLEAN_CODE_PROJECT_CIRCLE_HPP

#include "Headers/Base.hpp"
#include "Headers/Line.hpp"

#include "Headers/InputValidation.hpp"
#include "Headers/MathFunctions.hpp"

class Circle: public BaseShape
{
public:
    Circle();
    Circle(const Point*, const std::string&, const double&);

    void setSize(const Point&) override;

    void print() const override;

    const Point getAdditionalPoints() const override;

private:
	double radius;
};

#endif
