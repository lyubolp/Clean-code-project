#pragma once
#include "Base.h"

class Rectangle: public BaseShape
{
private:
	double width;
	double height;
public:
	Rectangle();
	Rectangle(const point*, const std::string, const double, const double);
	
	point getAdditionalPoints() const override;
	void setSize(const point) override;

};