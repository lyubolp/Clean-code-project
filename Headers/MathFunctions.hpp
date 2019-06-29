#pragma once
#include <iostream>
#include <cmath>

inline bool checkIfDoubleIsInInterval(const double toCheck, const std::pair<double, double> interval)
{
    return (interval.first <= toCheck) && (toCheck <= interval.second);
}
inline double getDistanceBetweenTwoPoints(const Point &a, const Point &b)
{
    return sqrt(pow((b.getX() - a.getX()),2) + pow((b.getY() - a.getY()),2));
}

inline bool isNumberBiggerThanZero(const int numberToCheck)
{
    return numberToCheck > 0;
}
inline bool isNumberBiggerThanZero(const double numberToCheck)
{
    return numberToCheck > 0;
}
