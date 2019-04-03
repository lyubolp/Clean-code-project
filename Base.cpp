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

void BaseShape::setPoints(const point pointsToSet, int amountOfPoints) //Sets a point based on point number (1-n), where n is the number of points;
{
	//This needs to be optimized
	//This is an abstract function
	point* newPoints = new point[pointsCount];

	for (int i = 0; i < amountOfPoints-1; i++)
	{
	newPoints[i] = points[i];
	}
	newPoints[amountOfPoints-1] = pointsToSet;
	for (int i = amountOfPoints; i < pointsCount; i++)
	{
	newPoints[i] = points[i];
	}

	delete[] points;
	points = newPoints;
}
void BaseShape::setPoints(const double xCoordinate, const double yCoordinate, int indexOfThePointToChange)
{
	//This needs to be optimized
	//This is an abstract function
	
	point* newPoints = new point[pointsCount];

	for (int i = 0; i < indexOfThePointToChange - 1; i++)
	{
	newPoints[i] = points[i];
	}
	newPoints[indexOfThePointToChange - 1].x = xCoordinate;
	newPoints[indexOfThePointToChange - 1].y = yCoordinate;
	for (int i = indexOfThePointToChange; i < pointsCount; i++)
	{
	newPoints[i] = points[i];
	}

	delete[] points;
	points = newPoints;
}
void BaseShape::setPoints(const point* pointsToSetAs, const int amountOfPoints) //All points
{
	//This needs to be optimized


	delete[] points;
	points = new point[amountOfPoints];

	for (int i = 0; i < amountOfPoints; i++)
	{
		points[i] = pointsToSetAs[i];
	}

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
	delete[] points;
}
std::ostream& operator<<(std::ostream& outputStream, point pointToPrint)
{
	outputStream << pointToPrint.x << " " << pointToPrint.y;
	return outputStream;
}