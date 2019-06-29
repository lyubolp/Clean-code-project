//
// Created by lyubo on 29.06.19.
//

#ifndef CLEAN_CODE_PROJECT_POINT_HPP
#define CLEAN_CODE_PROJECT_POINT_HPP


#include <iostream>

class Point
{

public:
    Point();
    Point(const double&, const double& );

    double getX() const;
    double getY() const;

    void setX(const double& x);
    void setY(const double&);
private:
    double x;
    double y;
};


#endif //CLEAN_CODE_PROJECT_POINT_HPP
