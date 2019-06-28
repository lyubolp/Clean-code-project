#pragma once
#include "Headers/Base.hpp"

class Line : public BaseShape
{
public:

    Line();
    Line(const point*, const std::string);

    void print() const override;

private:
    const point getAdditionalPoints() const override;

    void setSize(const point&) override;


};