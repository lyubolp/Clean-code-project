#include "Base.h"
#include <cstring>
BaseShape::BaseShape()
{
	points = new point[0];
	pointsCount = 0;

	color = new char[1];
	color = '\0';
	shapeType = Default;
}
BaseShape::BaseShape(const point* arrayOfPoints, const int amountOfPoints, const std::string shapeColor, const shape typeOfShape):color(shapeColor), shapeType(typeOfShape), pointsCount(amountOfPoints)
{
	points = new point[amountOfPoints];

	for (int i = 0; i < amountOfPoints; i++)
	{
		points[i] = arrayOfPoints[i];
	}
}
BaseShape::BaseShape(const BaseShape& rhs) :color(rhs.color), shapeType(rhs.shapeType), pointsCount(rhs.pointsCount)
{
	
	points = new point[rhs.pointsCount];
	for (int i = 0; i < rhs.pointsCount; i++)
	{
		points[i] = rhs.points[i];
	}
}


BaseShape& BaseShape::operator=(const BaseShape& rhs)
{
	if (this != &rhs)
	{
		color = rhs.color;

		delete[] points;
		points = new point[rhs.pointsCount];
		for (int i = 0; i < rhs.pointsCount; i++)
		{
			points[i] = rhs.points[i];
		}
		shapeType = rhs.shapeType;
		pointsCount = rhs.pointsCount;

	}
	return *this;
}

void BaseShape::deleteDynamicArray(point* objectToDelete)
{
	delete[] objectToDelete;
}

void BaseShape::replaceDynamicArray(point* destination,const point* source, const int sizeOfBothArrays)
{
	deleteDynamicArray(destination);

	copyDynamicArray(destination, source, sizeOfBothArrays);
}

void BaseShape::copyDynamicArray(point* destination, const point* source, const int sizeOfBothArrays)
{
	destination = new point[sizeOfBothArrays];

	for (int i = 0; i < sizeOfBothArrays; i++)
	{
		destination[i] = source[i];
	}
}
point* BaseShape::insertObjectIntoArray(std::pair<point, const int> objectToInsertAtPosition, std::pair<point*, const int> arrayToBeInsertedInWithItsSize)
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
void BaseShape::setTypeOfShape(const shape type)
{
	shapeType = type;
}
void BaseShape::setPointCount(const int amountOfPoints)
{
	pointsCount = amountOfPoints;
}
void BaseShape::setColor(const std::string shapeColor)
{
	color = shapeColor;
}
shape BaseShape::getType() const
{
	return shapeType;
}
point* BaseShape::getPoints() const
{
	return points;
}
int BaseShape::getPointsCount() const
{
	return pointsCount;
}
std::string BaseShape::getColor() const
{
	return color;
}

void BaseShape::setPoints(const point pointToBeReplacedWith, int indexOfPointsToSet) //Sets a point based on point number (1-n), where n is the number of points;
{
	point* newPoints = insertObjectIntoArray({ pointToBeReplacedWith, indexOfPointsToSet }, { points, pointsCount });

	deleteDynamicArray(points);
	replaceDynamicArray(points, newPoints, pointsCount);
}
void BaseShape::setPoints(const double xCoordinate, const double yCoordinate, int indexOfThePointToChange)
{
	point* newPoints = insertObjectIntoArray({point(xCoordinate, yCoordinate), indexOfThePointToChange }, { points, pointsCount });

	deleteDynamicArray(points);
	replaceDynamicArray(points, newPoints, pointsCount);
}
void BaseShape::setPoints(const point* pointsToSetAs, const int amountOfPoints) //All points
{
	deleteDynamicArray(points);
	replaceDynamicArray(points, pointsToSetAs, amountOfPoints);

	pointsCount = amountOfPoints;
}

void BaseShape::translate(const int horizontal, const int vertical)
{
	for (int i = 0; i < pointsCount; i++)
	{
		points[i].x += horizontal;
		points[i].y += vertical;
	}
}

point BaseShape::getAdditionalPoints() const
{
	return point(0, 0);
}

void BaseShape::setSize(const point)
{
}

BaseShape::~BaseShape()
{
	deleteDynamicArray(points);
}
std::ostream& operator<<(std::ostream& outputStream, point pointToPrint)
{
	outputStream << pointToPrint.x << " " << pointToPrint.y;
	return outputStream;
}