#pragma once
#include "Headers/Base.hpp"
#include "MathFunctions.hpp"

inline void deleteDynamicArray(point* objectToDelete)
{
	delete[] objectToDelete;
}

inline point* copyDynamicArray(const point* source, const int sizeOfBothArrays)
{
    if(sizeOfBothArrays < 1)
    {
        throw std::invalid_argument("Invalid size");
    }

    auto* destination = new point[sizeOfBothArrays];

    for (int i = 0; i < sizeOfBothArrays; i++)
    {
        destination[i] = source[i];
    }

    return destination;
}
inline point* replaceDynamicArray(const point* source, const int sizeOfBothArrays)
{
    if(sizeOfBothArrays < 1)
    {
        throw std::invalid_argument("Invalid size");
    }
	return copyDynamicArray(source, sizeOfBothArrays);
}

inline point* insertObjectIntoArray(std::pair<point, const int> objectToInsertAtPosition, std::pair<point*, const int> arrayToBeInsertedInWithItsSize)
{
    if(arrayToBeInsertedInWithItsSize.second < 1 || objectToInsertAtPosition.second < 0)
    {
        throw std::invalid_argument("Invalid size or position");
    }

    bool isXisLessThanZero = !isNumberBiggerThanZero(objectToInsertAtPosition.first.x);
    bool isYisLessThanZero = !isNumberBiggerThanZero(objectToInsertAtPosition.first.y);

    if(isXisLessThanZero || isYisLessThanZero)
    {
        throw std::invalid_argument("The coordinates of the point should non-negative");
    }

    auto* resultArray = new point[arrayToBeInsertedInWithItsSize.second + 1];

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

inline bool isNullptr(const point* pointToCheck)
{
	return pointToCheck == nullptr;
}