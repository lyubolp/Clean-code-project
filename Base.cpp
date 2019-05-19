#include "Headers/Base.h"
#include <cstring>
#include "Headers/DynamicMemoryManagment.h"
#include "Headers/InputValidation.h"
BaseShape::BaseShape()
{
	points = new point[0];
	pointsCount = 0;

	color = new char[1];
	color = '\0';
	shapeType = DEFAULT;
}
BaseShape::BaseShape(const point* arrayOfPoints, const int amountOfPoints, const std::string shapeColor, const shape typeOfShape):color(shapeColor), shapeType(typeOfShape), pointsCount(amountOfPoints)
{
    bool isNumberNotBiggerThanZero = !isNumberBiggerThanZero(amountOfPoints);
	if (isNumberNotBiggerThanZero)
	{
		std::cout << "Amount of points is invalid. Setting default for the type of shape...\n";
		if (typeOfShape == RECTANGLE || typeOfShape == CIRCLE)
		{
			pointsCount = 1;
		}
		else if (typeOfShape == LINE)
		{
			pointsCount = 2;
		}
		else if (typeOfShape == POLYGON)
		{
			std::cout << "Shape is polygon, creating default triangle...\n";
			pointsCount = 3;
		}
	}

	bool isColorStringNotValid = !isColorStringValid(color);
	if (isColorStringNotValid)
	{
		std::cout << "The color is not valid. The default color (black) is set.";
		color = "#000000";
	}

	if (isNullptr(arrayOfPoints))
	{
		std::cout << "Points are nullptr...\n Setting default point (0,0)";
		
		points = new point[1];
		points[0].x = 0;
		points[0].y = 0;
	}
	else
	{
		points = new point[pointsCount];

		for (int i = 0; i < pointsCount; i++)
		{
			points[i] = arrayOfPoints[i];
		}
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
        shapeType = rhs.shapeType;

        pointsCount = rhs.pointsCount;

        delete[] points;
        points = new point[rhs.pointsCount];
        for (int i = 0; i < rhs.pointsCount; i++)
        {
            points[i] = rhs.points[i];
        }

        color = rhs.color;
	}
	return *this;
}


void BaseShape::setTypeOfShape(const shape type)
{
	shapeType = type;
}
void BaseShape::setPointCount(const int amountOfPoints)
{
	if (isNumberBiggerThanZero(amountOfPoints))
	{
		pointsCount = amountOfPoints;
	}
	else
	{
		std::cout << "Invalid amount of points";
		return;
	}
	
}
void BaseShape::setColor(const std::string shapeColor)
{
	if (isColorStringValid(shapeColor))
	{
		color = shapeColor;
	}
	else
	{
		std::cout << "Invalid color\n";
		return;
	}
	
}
const shape BaseShape::getType() const
{
	return shapeType;
}
const point * BaseShape::getPoints() const
{
	return points;
}
const int BaseShape::getPointsCount() const
{
	return pointsCount;
}
const std::string BaseShape::getColor() const
{
	return color;
}

void BaseShape::setPoints(const point pointToBeReplacedWith, int indexOfPointsToSet) //Sets a point based on point number (1-n), where n is the number of points;
{
	if (isNumberBiggerThanZero(indexOfPointsToSet))
	{
		point* newPoints = insertObjectIntoArray({ pointToBeReplacedWith, indexOfPointsToSet }, { points, pointsCount });
		deleteDynamicArray(points);
		replaceDynamicArray(points, newPoints, pointsCount);
	}
	else
	{
		std::cout << "Invalid index \n";
		return;
	}
}
void BaseShape::setPoints(const double xCoordinate, const double yCoordinate, int indexOfThePointToChange)
{
	if (isNumberBiggerThanZero(indexOfThePointToChange) && indexOfThePointToChange < pointsCount)
	{
		point* newPoints = insertObjectIntoArray({ point(xCoordinate, yCoordinate), indexOfThePointToChange }, { points, pointsCount });

		deleteDynamicArray(points);
		replaceDynamicArray(points, newPoints, pointsCount);
	}
	else
	{
		std::cout << "Invalid index \n";
		return;
	}
}
void BaseShape::setPoints(const point* pointsToSetAs, const int amountOfPoints) //All points
{
	if (isNumberBiggerThanZero(amountOfPoints) && !isNullptr(pointsToSetAs))
	{
		deleteDynamicArray(points);
		replaceDynamicArray(points, pointsToSetAs, amountOfPoints);

		pointsCount = amountOfPoints;
	}
	else
	{
		std::cout << "Index or pointer error";
		return;
	}
	
}

void BaseShape::translate(const int horizontal, const int vertical)
{
	if (isNumberBiggerThanZero(horizontal) && isNumberBiggerThanZero(vertical))
	{
		for (int i = 0; i < pointsCount; i++)
		{
			points[i].x += horizontal;
			points[i].y += vertical;
		}
	}
	else
	{
		std::cout << "Invalid coordinates";
		return;
	}
	
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