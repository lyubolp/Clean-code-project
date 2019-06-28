#pragma once
#include "Headers/Base.hpp"
class Polygon : public BaseShape
{
public:
	Polygon();
	Polygon(const point*, int,const std::string);

    void print() const override;
};