#include <cstring>

#include "Headers/Base.hpp"
#include "Headers/DynamicMemoryManagment.hpp"
#include "Headers/InputValidation.hpp"

BaseShape::BaseShape()
{
    //Setup a base shape, with no points, no color
	points = nullptr;
	pointsCount = 0;

	color = "";

	shapeType = DEFAULT;
}

BaseShape::BaseShape(const std::pair<const Point*,const int>& newPoints, const std::string& shapeColor, const shape& typeOfShape)
{
    //We use the setter to set all fields with the data from the constructor
    points = nullptr;
    setAllFields(newPoints, shapeColor, typeOfShape);
}

BaseShape::BaseShape(const BaseShape& rhs) : BaseShape({rhs.points, rhs.pointsCount}, rhs.color, rhs.shapeType)
{
    //Copy constructor
}

BaseShape& BaseShape::operator=(const BaseShape& rhs)
{
	if (this != &rhs)
	{
        delete[] points;
        setAllFields(std::pair<const Point *, const int>(rhs.getPoints(), rhs.getPointsCount()), rhs.getColor(),
                     rhs.getType());
	}
	return *this;
}

BaseShape::~BaseShape()
{
    deleteDynamicArray(points);
}

const shape BaseShape::getType() const
{
	return shapeType;
}

const std::string BaseShape::getColor() const
{
    return color;
}

const Point * BaseShape::getPoints() const
{
	return points;
}
const int BaseShape::getPointsCount() const
{
	return pointsCount;
}

void BaseShape::translate(const int& horizontal, const int& vertical)
{
    //Translating the shape
    //First we need to validate the data
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
		throw std::invalid_argument("Invalid coordinates");
	}
}

void BaseShape::setAllFields(const std::pair<const Point *, const int> &newPoints, const std::string &shapeColor, const shape &typeOfShape)
{
    try
    {
        setPoints(newPoints.first, newPoints.second);
    }
    catch(std::invalid_argument& e)
    {
        throw e;
    }

    try
    {
        setPointCount(newPoints.second);
    }
    catch(std::out_of_range& e)
    {
        throw e;
    }

    setColor(shapeColor);
    setTypeOfShape(typeOfShape);
}

void BaseShape::setTypeOfShape(const shape& type)
{
    shapeType = type;
}

void BaseShape::setColor(const std::string& shapeColor)
{
    if (isColorStringValid(shapeColor))
    {
        color = shapeColor;
    }
    else
    {
        std::cout << "Invalid color... setting to #FFFFFF";
        color = "#FFFFFF";
    }
}

void BaseShape::setPoints(const Point& pointToBeReplacedWith, const int& indexOfPointsToSet)
{
    //Sets a Point based on Point number (1-n), where n is the number of points;
    if (isNumberBiggerThanZero(indexOfPointsToSet))
    {
        Point* newPoints = insertObjectIntoArray({ pointToBeReplacedWith, indexOfPointsToSet }, { points, pointsCount });
        deleteDynamicArray(points);

        try
        {
            points = replaceDynamicArray(newPoints, pointsCount);
        }
        catch(std::invalid_argument& e)
        {
            std::cout << e.what();
            throw std::invalid_argument("Invalid argument");
        }
    }
    else
    {
        throw std::invalid_argument("Invalid argument");
    }
}

void BaseShape::setPoints(const double& xCoordinate, const double& yCoordinate, const int& indexOfThePointToChange)
{
    if (isNumberBiggerThanZero(indexOfThePointToChange) && indexOfThePointToChange < pointsCount)
    {
        Point* newPoints = insertObjectIntoArray({ Point(xCoordinate, yCoordinate), indexOfThePointToChange }, { points, pointsCount });

        deleteDynamicArray(points);

        try
        {
            points = replaceDynamicArray(newPoints, pointsCount);
        }
        catch(std::invalid_argument& e)
        {
            std::cout << e.what();
            throw std::invalid_argument("Invalid argument");
        }
    }
    else
    {
        throw std::invalid_argument("Invalid Point index");
    }
}

void BaseShape::setPoints(const Point* pointsToSetAs, const int& amountOfPoints) //All points
{
    if (isNumberBiggerThanZero(amountOfPoints) && !isNullptr(pointsToSetAs))
    {
        try
        {
            deleteDynamicArray(points);
            points = replaceDynamicArray(pointsToSetAs, amountOfPoints);
        }
        catch(std::invalid_argument& e)
        {
            throw e;
        }

        pointsCount = amountOfPoints;
    }
    else
    {
        throw std::out_of_range("Out of range");
    }

}

void BaseShape::setPointCount(const int& amountOfPoints)
{
    if (isNumberBiggerThanZero(amountOfPoints))
    {
        pointsCount = amountOfPoints;
    }
    else
    {
        throw std::out_of_range("Invalid amount of points");
    }

}

std::ostream& operator<<(std::ostream& outputStream, Point pointToPrint)
{
	outputStream << pointToPrint.x << " " << pointToPrint.y;
	return outputStream;
}