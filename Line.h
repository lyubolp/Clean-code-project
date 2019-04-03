#pragma once
#include "Base.h"

class Line : public BaseShape
{
private:

	point getAdditionalPoints() const override;
	void setSize(const point) override;
public:
	Line();
	Line(const point*, const std::string);
	
};