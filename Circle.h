#pragma once
#include "Base.h"

class Circle: public BaseShape
{
private:
	double radius;
public:
	Circle();
	Circle(const point*, const std::string, double);

	point getAdditionalPoints() const override;
	void setSize(const point) override;

	/*
	point getRadius() const;
	void setRadius(const int) ;*/
};
