#pragma once
#include "Headers/Base.h"
class Polygon : public BaseShape
{
private:

public:
	Polygon();
	Polygon(const point*, int,const std::string);

    void print() const override;
};