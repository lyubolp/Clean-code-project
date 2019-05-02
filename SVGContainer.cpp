#include "SVGContainer.h"
#include "StringManip.cpp"
#include <iostream>
#include <cmath>

SVGContainer::SVGContainer() :itemCount(0)
{
	//items = new Base[0];
}

SVGContainer::SVGContainer(const std::vector<BaseShape*> containerOfShapes) : itemCount(1)
{
	shapes = containerOfShapes;
}

SVGContainer::SVGContainer(const SVGContainer& objectToCopyFrom)
{
	shapes = objectToCopyFrom.shapes;
	itemCount = objectToCopyFrom.itemCount;
}

SVGContainer& SVGContainer::operator=(const SVGContainer& objectToCopyFrom)
{
	if (this != &objectToCopyFrom)
	{
		shapes = objectToCopyFrom.shapes;
		itemCount = objectToCopyFrom.itemCount;
	}
	return *this;
}

void SVGContainer::printRectangle(const BaseShape* shapeToPrint) const
{
	std::cout << "rectangle " << shapeToPrint->getPoints() << " " << shapeToPrint->getAdditionalPoints() << " " << shapeToPrint->getColor() << "\n";
}

void SVGContainer::printCircle(const BaseShape* shapeToPrint) const
{
	std::cout << "circle " << shapeToPrint->getPoints() << " " << shapeToPrint->getAdditionalPoints().x << " " << shapeToPrint->getColor() << "\n";

}

void SVGContainer::printLine(const BaseShape* shapeToPrint) const
{
	point* pointsOfTheShapeToPrint; //We get the points of the current object
	pointsOfTheShapeToPrint = shapeToPrint->getPoints(); //Get the points

	std::cout << "line " << pointsOfTheShapeToPrint[0] << " " << pointsOfTheShapeToPrint[1] << " " << shapeToPrint->getColor() << "\n";
}

void SVGContainer::printPolygon(const BaseShape* shapeToPrint) const
{
	point* pointsOfTheShapeToPrint; //We get the points of the current object
	pointsOfTheShapeToPrint = shapeToPrint->getPoints(); //Get the points

	std::cout << "polygon ";
	int pointsCountOfTheShapeToPrint = shapeToPrint->getPointsCount();

	for (int i = 0; i < pointsCountOfTheShapeToPrint; i++) //The polygon has an unknown amount of points
	{
		std::cout << pointsOfTheShapeToPrint[i] << " ";
	}
	std::cout << shapeToPrint->getColor() << "\n";
}


bool SVGContainer::checkIfIntIsInInterval(const int toCheck, const std::pair<int, int> interval)
{
	return (interval.first <= toCheck) && (toCheck <= interval.second);
}

bool SVGContainer::checkIfPointIsWithinRectangle(const Rectangle & bound, const point & pointToCheck)
{
	int rectangleAX = bound.getPoints()->x;
	int rectangleAY = bound.getPoints()->y;

	int rectangleBX = rectangleAX + bound.getAdditionalPoints().x;
	int rectangleCY = rectangleAY + bound.getAdditionalPoints().y;

	return checkIfIntIsInInterval(pointToCheck.x, { rectangleAX,rectangleBX }) && checkIfIntIsInInterval(pointToCheck.y, { rectangleAY, rectangleCY });
}

bool SVGContainer::checkIfRectangleIsWithinRectangle(const Rectangle &bound, const BaseShape& objectToCheck)
{
	point rectangleDiagonalPointA = point(objectToCheck.getPoints()->x, objectToCheck.getPoints()->y);
	point rectangleDiagonalPointB = point(rectangleDiagonalPointA.x + objectToCheck.getAdditionalPoints().x, rectangleDiagonalPointA.y + objectToCheck.getAdditionalPoints().y);

	return checkIfPointIsWithinRectangle(bound, rectangleDiagonalPointA) && checkIfPointIsWithinRectangle(bound, rectangleDiagonalPointB);
}

bool SVGContainer::checkIfCircleIsWithinRectangle(const Rectangle & bound, const BaseShape & objectToCheck)
{
	point centerOfNewRectangle(objectToCheck.getPoints()->x, objectToCheck.getPoints()->y - objectToCheck.getAdditionalPoints().x);
	point widthPointOfNewRectangle(objectToCheck.getPoints()->x + objectToCheck.getAdditionalPoints().x, objectToCheck.getPoints()->y);
	point heightPointOfNewRectangle(objectToCheck.getPoints()->x - objectToCheck.getAdditionalPoints().x, objectToCheck.getPoints()->y);
	Rectangle circleMaxBounds(&centerOfNewRectangle, "#000000", getDistanceBetweenTwoPoints(centerOfNewRectangle, widthPointOfNewRectangle), getDistanceBetweenTwoPoints(centerOfNewRectangle, heightPointOfNewRectangle));

	return checkIfRectangleIsWithinRectangle(bound, circleMaxBounds);
}

bool SVGContainer::checkIfLineIsWithinRectangle(const Rectangle & bound, const BaseShape & objectToCheck)
{

	return checkIfPointIsWithinRectangle(bound, objectToCheck.getPoints()[0]) && checkIfPointIsWithinRectangle(bound, objectToCheck.getPoints()[1]);
}

bool SVGContainer::checkIfPolygonIsWithinRectangle(const Rectangle & bound, const BaseShape & objectToCheck)
{
	int amountOfPointsInShape = objectToCheck.getPointsCount();

	bool result = true;
	for (int i = 0; i < amountOfPointsInShape; i++)
	{
		if (!checkIfPointIsWithinRectangle(bound, objectToCheck.getPoints()[i]))
		{
			result = false;
			return result;
		}
	}

	return result;
}

bool SVGContainer::checkIfPointIsWithinCircle(const Circle & bound, const point & pointToCheck)
{
	int radius = bound.getAdditionalPoints().x;
	return ((pow((pointToCheck.x - bound.getPoints()->x), 2) + pow((pointToCheck.y - bound.getPoints()->y), 2)) <= pow(radius, 2));
}

bool SVGContainer::checkIfRectangleIsWithinCircle(const Circle & bound, const BaseShape & objectToCheck)
{
	point rectanglePointA = *(objectToCheck.getPoints());
	point rectanglePointB(rectanglePointA.x + objectToCheck.getAdditionalPoints().x, rectanglePointA.y);
	point rectanglePointC(rectanglePointA.x, rectanglePointA.y + objectToCheck.getAdditionalPoints().y);
	point rectanglePointD(rectanglePointA.x + objectToCheck.getAdditionalPoints().x, rectanglePointA.y + objectToCheck.getAdditionalPoints().y);


	return checkIfPointIsWithinCircle(bound, rectanglePointA) && checkIfPointIsWithinCircle(bound, rectanglePointB) && checkIfPointIsWithinCircle(bound, rectanglePointC) && checkIfPointIsWithinCircle(bound, rectanglePointD);
}

bool SVGContainer::checkIfCircleIsWithinCircle(const Circle & bound, const BaseShape & objectToCheck)
{
	double distanceBetweenCenterOfBothCircles = getDistanceBetweenTwoPoints(*bound.getPoints(), *objectToCheck.getPoints());

	return ((objectToCheck.getAdditionalPoints().x + distanceBetweenCenterOfBothCircles) < bound.getAdditionalPoints().x);
}

bool SVGContainer::checkIfLineIsWithinCircle(const Circle & bound, const BaseShape & objectToCheck)
{
	return checkIfPointIsWithinCircle(bound, objectToCheck.getPoints()[0]) && checkIfPointIsWithinCircle(bound, objectToCheck.getPoints()[1]);
}

bool SVGContainer::checkIfPolygonIsWithinCircle(const Circle &bound, const BaseShape &objectToCheck)
{

	int amountOfPointsInShape = objectToCheck.getPointsCount();

	bool result = true;
	for (int i = 0; i < amountOfPointsInShape; i++)
	{
		if (!checkIfPointIsWithinCircle(bound, objectToCheck.getPoints()[i]))
		{
			result = false;
			return result;
		}
	}

	return result;
}

double SVGContainer::getDistanceBetweenTwoPoints(const point &a, const point &b)
{
	return sqrt(pow((b.x - a.x),2) + pow((b.y - a.y),2));
}

shape SVGContainer::checkTypeOfShape(BaseShape* toCheck)
{
	return toCheck->getType();
}

Rectangle* SVGContainer::createRectangleFromUserInput(const std::string userInput)
{
	int indexOfWordRectangle = userInput.find("rectangle");
	if (indexOfWordRectangle != -1)
	{
		double xCoordinate, yCoordinate, width, height;
		std::string color;

		std::string inputWithoutRectangle = userInput.substr(indexOfWordRectangle + OFFSET_RECTANGLE_WORD); //We erase everything behind the <x> coordinate => r:=<x> <y> <width> <height> <color>

		xCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, " ");
		yCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, " ");
		width = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, " ");
		height = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, " ");
		color = cutFirstSubstringFromString(inputWithoutRectangle, " ");

		//Pushes the item to the vector
		point p(xCoordinate, yCoordinate);
		Rectangle* result = new Rectangle(&p, color, width, height);

		return result;
	}
	else
	{
		std::cout << "Error !";
		return nullptr;
	}

}

Circle* SVGContainer::createCircleFromUserInput(const std::string userInput)
{
	int indexOfWordCircle = userInput.find("circle");
	if (indexOfWordCircle != -1)
	{
		double xCoordinate, yCoordinate, radius;
		std::string color;
		
		std::string inputWithoutCircle = userInput.substr(indexOfWordCircle + OFFSET_CIRCLE_WORD); //We erase everything behind the <x> coordinate => r:=<x> <y> <width> <height> <color>

		xCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutCircle, " ");
		yCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutCircle, " ");
		radius = cutFirstNumberFromStringAsDouble(inputWithoutCircle, " "); 
		color = cutFirstSubstringFromString(inputWithoutCircle, " ");

		point p(xCoordinate, yCoordinate);
		Circle* result = new Circle(&p, color, radius);
		
		return result;

	}
	else
	{
		std::cout << "Error !";
		return nullptr;
	}
}

Line* SVGContainer::createLineFromUserInput(const std::string userInput)
{
	int indexOfWordLine = userInput.find("line");
	if (indexOfWordLine != 1)
	{
		double x1, y1, x2, y2;
		std::string color;

		std::string inputWithoutLine = userInput.substr(indexOfWordLine + OFFSET_LINE_WORD); //We erase everything behind the <x> coordinate => r:=<x> <y> <width> <height> <color>

		x1 = cutFirstNumberFromStringAsDouble(inputWithoutLine, " ");
		y1 = cutFirstNumberFromStringAsDouble(inputWithoutLine, " ");

		x2 = cutFirstNumberFromStringAsDouble(inputWithoutLine, " ");
		y2 = cutFirstNumberFromStringAsDouble(inputWithoutLine, " ");
		color = cutFirstSubstringFromString(inputWithoutLine, " ");

		//Pushes the item to the vector
		point* p = new point[2];
		point p1(x1, y1);
		point p2(x2, y2);
		p[0] = p1;
		p[1] = p2;

		Line* result = new Line(p, color);
		return result;
	}
}

Polygon* SVGContainer::createPolygonFromUserInput(const std::string userInput)
{
	int indexOfWordPolygon = userInput.find("polygon");
	if (indexOfWordPolygon != 1)
	{
		std::string inputWithoutPolygon = userInput.substr(indexOfWordPolygon + OFFSET_POLYGON_WORD), color;
		int amountOfPoints = countChar(inputWithoutPolygon, SPACE_ASCII) - 1; //We also have one ' ' for the color

		double  x, y;
		
		if (amountOfPoints % 2 == 0) 
		{
			point* p = new point[amountOfPoints / 2];
			for (int i = 0; i < amountOfPoints / 2; i++)
			{
				x = cutFirstNumberFromStringAsDouble(inputWithoutPolygon, " ");
				y = cutFirstNumberFromStringAsDouble(inputWithoutPolygon, " ");
				p[i] = point(x, y);
			}
			color = cutFirstSubstringFromString(inputWithoutPolygon, " ");

			Polygon* result = new Polygon(p, amountOfPoints / 2, color);

			return result;
		}
		else
		{
			std::cout << "Invalid command\n";
		}

		return nullptr;
	}
}

void SVGContainer::printShapes(int idOfTheShapeToPrint)
{
	//This function prints only one object
	//<id>. <type> <array_of_points> <additional> <color>

	//<rectangle>:= <id> <type> <x> <y> <width> <height> <color>
	//<circle>:= <id> <type> <x> <y> <radius> <color>
	//<line>:= <id> <type> <x1> <y1> <x2> <y2> <color>
	//<polygon>:= <id> <type> <point1> <point2> ... <pointN> <color>

	//1. rectangle 5 5 10 10 green
	//2. circle 5 5 10 blue
	//3. rectangle 100 60 10 10 red
	//4. polygon 12 12 12
	//5. line 1 1 2 2

	std::cout << idOfTheShapeToPrint + 1 << ". "; //Prints the id-s

	BaseShape* shapeToPrint = shapes[idOfTheShapeToPrint];
	shape typeOfShapeToPrint = checkTypeOfShape(shapeToPrint);

	if (typeOfShapeToPrint == RectangleT) //We check the type of the figure & we print the data
	{
		printRectangle(shapeToPrint);
	}
	else if (typeOfShapeToPrint == CircleT)
	{
		printCircle(shapeToPrint);
	}
	else if (typeOfShapeToPrint == LineT)
	{
		printLine(shapeToPrint);
	}
	else if (typeOfShapeToPrint == PolygonT)
	{
		printPolygon(shapeToPrint);
	}
	else
	{
		std::cout << "Invalid shape!";
		return;
	}
}

void SVGContainer::printShapes()
{
	//If we want to print all objects, we just make a loop
	for (int i = 0; i < itemCount; i++)
	{
		printShapes(i);
	}
}

void SVGContainer::createShape(const std::string userInput)
{
	//If the command is in this function, it contains create
	//User input format:
	//create <figure> <points> <additionalPoints> <color>

	//<rectangle> := create rectangle <x> <y> <width> <height> <color>
	//<circle> := create circle <x> <y> <r> <color>
	//<line> := create line <x1> <y1> <x2> <y2> <color>
	//<polygon> := create polygon <point1> <point2> ... <pointN> <color>

	//create rectangle 1000 1000 10 20 yellow
	
	itemCount++;
	
	if (userInput[INSERT_COMMAND_FIRST_LETTER_OF_SHAPE_LOCATION] == FIRST_LETTER_RECTANGLE)
	{
		if (countChar(userInput, SPACE_ASCII) < AMOUNT_WHITESPACE_COMMAND_RECTANGLE)
		{
			std::cout << "Invalid command\n";
		}
		else
		{
			Rectangle* temp = createRectangleFromUserInput(userInput);
			shapes.push_back(temp);
		}
		
	}
	else if (userInput[INSERT_COMMAND_FIRST_LETTER_OF_SHAPE_LOCATION] == FIRST_LETTER_CIRCLE)
	{
		if (countChar(userInput, SPACE_ASCII) < AMOUNT_WHITESPACE_COMMAND_CIRCLE)
		{
			std::cout << "Invalid command\n";
		}
		else
		{
			Circle* temp = createCircleFromUserInput(userInput);
			shapes.push_back(temp);
		}
	}
	else if (userInput[INSERT_COMMAND_FIRST_LETTER_OF_SHAPE_LOCATION] == FIRST_LETTER_LINE)
	{
		if (countChar(userInput, SPACE_ASCII) < AMOUNT_WHITESPACE_COMMAND_LINE)
		{
			std::cout << "Invalid command\n";
		}
		else
		{
			Line* temp = createLineFromUserInput(userInput);
			shapes.push_back(temp);
		}
	}
	else if (userInput[INSERT_COMMAND_FIRST_LETTER_OF_SHAPE_LOCATION] == FIRST_LETTER_POLYGON)
	{	
		Polygon* temp = createPolygonFromUserInput(userInput);
		shapes.push_back(temp);
	}
	else
	{
		std::cout << "Error with command!";
		return;
	}
}

void SVGContainer::eraseShape(const int idOfTheShapeToErase)
{
	if (idOfTheShapeToErase <= itemCount) //If the figure exists
	{
		std::vector<BaseShape*>::iterator it = shapes.begin(); 
		shapes.erase(it + (idOfTheShapeToErase - 1)); //We find the one we need to delete
		std::cout << "Deleted successfully  figure " << idOfTheShapeToErase << "\n";
		itemCount--;
	}
	else 
	{
		std::cout << "There is no figure " << idOfTheShapeToErase << "\n";
	}
}

void SVGContainer::eraseShape(const std::string userInput)
{
	int indexOfWordErase = userInput.find("erase");
	eraseShape(std::stoi(userInput.substr(indexOfWordErase + OFFSET_ERASE_WORD)));
}

void SVGContainer::translateShape(const std::string coordinates)
{
	//translate vertical=10 horizontal=100
	//translate 1 vertical=20 horizontal=200

	int indexOfWordTranslate = coordinates.find("translate");
	int idOfFigureToTranslate = -1;
	double vertical, horizontal;
	std::string inputWithoutTranslate = coordinates.substr(indexOfWordTranslate + OFFSET_TRANSLATE_WORD); //removes translate 
	
	if (inputWithoutTranslate[0] != FIRST_LETTER_VERTICAL)
	{
		//Input has id
		idOfFigureToTranslate = cutFirstNumberFromStringAsInt(inputWithoutTranslate, " ");
	}

	inputWithoutTranslate = removeWordFromString("vertical=", inputWithoutTranslate);
	vertical = cutFirstNumberFromStringAsDouble(inputWithoutTranslate, " ");

	inputWithoutTranslate = removeWordFromString("horizontal=", inputWithoutTranslate);
	horizontal = cutFirstNumberFromStringAsDouble(inputWithoutTranslate, " ");

	if (idOfFigureToTranslate == -1) //If we have to translate all figures, we loop them
	{
		int s = shapes.size();
		for (int i = 0; i < s; i++)
		{
			shapes[i]->translate(vertical, horizontal); 
		}
	}
	else
	{
		shapes[idOfFigureToTranslate]->translate(vertical, horizontal);//If we have 1 figure, we translate it
	}
	
}


bool SVGContainer::figureWithingARectanglePassedAsAnObject(const Rectangle& bound, const BaseShape & obj) //TO BE REFACTORED
{
	if (obj.getType() == RectangleT)
	{
		return checkIfRectangleIsWithinRectangle(bound, obj);
	}
	else if (obj.getType() == CircleT)
	{
		return checkIfCircleIsWithinRectangle(bound, obj);
	}
	else if (obj.getType() == LineT)
	{
		return checkIfLineIsWithinRectangle(bound, obj);
	}
	else if (obj.getType() == PolygonT)
	{
		return checkIfPolygonIsWithinRectangle(bound, obj);
	}
	else
	{
		std::cout << "Error";
		return false;
	}
}

bool SVGContainer::figureWithingACirclePassedAsAnObject(const Circle & bound, const BaseShape & obj)
{

	if (obj.getType() == RectangleT)
	{
		return checkIfRectangleIsWithinCircle(bound, obj);
	}
	else if (obj.getType() == CircleT)
	{
		return checkIfCircleIsWithinCircle(bound, obj);
	}
	else if (obj.getType() == LineT)
	{
		return checkIfLineIsWithinCircle(bound, obj);
	}
	else if (obj.getType() == PolygonT)
	{
		return checkIfPolygonIsWithinCircle(bound, obj);
	}
	return true;
}

void SVGContainer::figureWithingCommand(const std::string userInput) //TO BE REFACTORED
{
	//within circle 0 0 5

	//within rectangle <x> <y> <w> <h>
	//within circle <x> <y> <r>

	std::string inputWithoutWithin = removeFirstSubstringFromString(userInput, " ");

	if (inputWithoutWithin[0] == FIRST_LETTER_RECTANGLE)
	{
		int results;
		Rectangle bound = *createRectangleFromUserInput(inputWithoutWithin);

		for (int i = 0; i < itemCount; i++)
		{
			if (figureWithingARectanglePassedAsAnObject(bound, *shapes[i]))
			{
				printShapes(i);
				results++;
			}
		}
		if (results == 0)
		{
			std::cout << "No figures are located " << userInput;
		}
	}
	else if(inputWithoutWithin[0] == FIRST_LETTER_CIRCLE)
	{
		Circle bound = *createCircleFromUserInput(inputWithoutWithin);
		int results = 0;
		for (int i = 0; i < itemCount; i++)
		{
			if (figureWithingACirclePassedAsAnObject(bound, *shapes[i]))
			{
				printShapes(i);
				results++;
			}
		}
		if (results == 0)
		{
			std::cout << "No figures are located " << userInput;
		}
	}
	else
	{
		//Error

		return;
	}
}

void SVGContainer::openFromContainer(const std::vector<std::string> containerWithCommandsAsString)
{
	for (std::string input : containerWithCommandsAsString)
	{
		createShape(input);
	}
}

BaseShape* SVGContainer::getItem(const int idOfTheItem) const
{
	return shapes[idOfTheItem];
}

int SVGContainer::getCount() const
{
	return itemCount;
}

SVGContainer::~SVGContainer()
{
	int s = shapes.size();
	for (int i = 0; i < s; i++)
	{
		delete shapes[i];
	}
}
 