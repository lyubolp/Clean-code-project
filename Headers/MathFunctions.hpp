#pragma once
#include <iostream>
#include <cmath>

inline bool checkIfDoubleIsInInterval(const double toCheck, const std::pair<double, double> interval)
{
    return (interval.first <= toCheck) && (toCheck <= interval.second);
}
inline double getDistanceBetweenTwoPoints(const point &a, const point &b)
{
    return sqrt(pow((b.x - a.x),2) + pow((b.y - a.y),2));
}

inline bool isNumberBiggerThanZero(const int numberToCheck)
{
    return numberToCheck > 0;
}
inline bool isNumberBiggerThanZero(const double numberToCheck)
{
    return numberToCheck > 0;
}
