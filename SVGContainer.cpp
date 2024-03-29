#include "Headers/SVGContainer.hpp"
#include <iostream>
#include <cmath>

SVGContainer& SVGContainer::getInstance()
{
    static SVGContainer instance;

    return instance;
}



const shape SVGContainer::checkTypeOfShape(BaseShape * toCheck)
{
	return toCheck->getType();
}

void SVGContainer::addShape(BaseShape * shapeToAdd)
{
    shapes.push_back(shapeToAdd);
    itemCount++;
}

void SVGContainer::printShapes(int idOfTheShapeToPrint)
{
	//This function prints only one object
	//<id>. <type> <array_of_points> <additional> <color>

	//<rectangle>:= <id> <type> <x> <y> <width> <height> <color>
	//<circle>:= <id> <type> <x> <y> <radius> <color>
	//<line>:= <id> <type> <x1> <y1> <x2> <y2> <color>

	//1. rectangle 5 5 10 10 green
	//2. circle 5 5 10 blue
	//3. rectangle 100 60 10 10 red
	//4. line 1 1 2 2

	std::cout << idOfTheShapeToPrint + 1 << ". "; //Prints the id-s

	BaseShape* shapeToPrint = shapes[idOfTheShapeToPrint];
	shape typeOfShapeToPrint = checkTypeOfShape(shapeToPrint);

	if (typeOfShapeToPrint == RECTANGLE) //We check the type of the figure & we print the data
	{
        shapeToPrint->print();
	}
	else if (typeOfShapeToPrint == CIRCLE)
	{
		shapeToPrint->print();
	}
	else if (typeOfShapeToPrint == LINE)
	{
        shapeToPrint->print();
	}
	else
	{
		throw std::invalid_argument("Invalid shape");
	}
}

void SVGContainer::printShapes()
{
	//If we want to print all objects, we just make a loop
	for (int i = 0; i < itemCount; i++)
	{
		try
        {
		    printShapes(i);
        }
		catch(std::invalid_argument& e)
        {
		    throw e;
        }
	}
}

void SVGContainer::eraseShape(const int idOfTheShapeToErase)
{
	if (idOfTheShapeToErase <= itemCount) //If the figure exists
	{
		auto it = shapes.begin();
		shapes.erase(it + (idOfTheShapeToErase - 1));
		itemCount--;
	}
	else 
	{
	    throw std::out_of_range("No shape has index " + std::to_string(idOfTheShapeToErase));
	}
}


void SVGContainer::translateShape(const int & idOfFigureToTranslate , const double & vertical, const double & horizontal)
{
    try
    {
        shapes[idOfFigureToTranslate]->translate(vertical, horizontal);
    }
    catch (std::invalid_argument& e)
    {
        throw e;
    }
}


const BaseShape * SVGContainer::getItem(const int idOfTheItem) const
{
	return shapes[idOfTheItem];
}

const int SVGContainer::getCount() const
{
	return itemCount;
}


 