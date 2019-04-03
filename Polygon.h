#pragma once
#include "Base.h"
class Polygon : public Base
{
private:

	point getAdditionalPoints() const override;
	void setSize(const point) override;
public:
	Polygon();
	Polygon(const point*, int,const std::string);


};