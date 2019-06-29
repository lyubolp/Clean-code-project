#pragma once
#include "Headers/Base.hpp"
#include "MathFunctions.hpp"

inline void deleteDynamicArray(Point* objectToDelete)
{
	delete[] objectToDelete;
}

inline Point* copyDynamicArray(const Point* source, const int sizeOfBothArrays)
{
    if(sizeOfBothArrays < 1)
    {
        throw std::invalid_argument("Invalid size");
    }

    auto* destination = new Point[sizeOfBothArrays];

    for (int i = 0; i < sizeOfBothArrays; i++)
    {
        destination[i] = source[i];
    }

    return destination;
}
inline Point* replaceDynamicArray(const Point* source, const int sizeOfBothArrays)
{
    if(sizeOfBothArrays < 1)
    {
        throw std::invalid_argument("Invalid size");
    }
	return copyDynamicArray(source, sizeOfBothArrays);
}

inline Point* insertObjectIntoArray(std::pair<Point, const int> objectToInsertAtPosition, std::pair<Point*, const int> arrayToBeInsertedInWithItsSize)
{
    if(arrayToBeInsertedInWithItsSize.second < 1 || objectToInsertAtPosition.second < 0)
    {
        throw std::invalid_argument("Invalid size or position");
    }

    bool isXisLessThanZero = !isNumberBiggerThanZero(objectToInsertAtPosition.first.getX());
    bool isYisLessThanZero = !isNumberBiggerThanZero(objectToInsertAtPosition.first.getY());

    if(isXisLessThanZero || isYisLessThanZero)
    {
        throw std::invalid_argument("The coordinates of the Point should non-negative");
    }

    auto* resultArray = new Point[arrayToBeInsertedInWithItsSize.second + 1];

	for (int i = 0; i < objectToInsertAtPosition.second - 1; i++)
	{
		resultArray[i] = arrayToBeInsertedInWithItsSize.first[i];
	}

	resultArray[objectToInsertAtPosition.second - 1] = objectToInsertAtPosition.first;

	for (int i = objectToInsertAtPosition.second; i < arrayToBeInsertedInWithItsSize.second; i++)
	{
		resultArray[i] = arrayToBeInsertedInWithItsSize.first[i];
	}
	return resultArray;
}

inline bool isNullptr(const Point* pointToCheck)
{
	return pointToCheck == nullptr;
}