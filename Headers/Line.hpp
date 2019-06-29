#pragma once
#include "Headers/Base.hpp"

class Line : public BaseShape
{
public:

    Line();
    Line(const Point*, const std::string);

    void print() const override;

private:
    const Point getAdditionalPoints() const override;

    void setSize(const Point&) override;


};