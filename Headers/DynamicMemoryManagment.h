#pragma once
#include "Headers/Base.h"
inline void deleteDynamicArray(point* objectToDelete)
{
	delete[] objectToDelete;
}

inline void copyDynamicArray(point* destination, const point* source, const int sizeOfBothArrays)
{
    destination = new point[sizeOfBothArrays];

    for (int i = 0; i < sizeOfBothArrays; i++)
    {
        destination[i] = source[i];
    }
}
inline void replaceDynamicArray(point* destination, const point* source, const int sizeOfBothArrays)
{
	deleteDynamicArray(destination);

	copyDynamicArray(destination, source, sizeOfBothArrays);
}

inline point* insertObjectIntoArray(std::pair<point, const int> objectToInsertAtPosition, std::pair<point*, const int> arrayToBeInsertedInWithItsSize)
{
	point* resultArray = new point[arrayToBeInsertedInWithItsSize.second + 1];
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