#pragma once
#include "Base.h"
#include "Rectangle.h"
#include "Polygon.h"
#include "Line.h"
#include "Circle.h"
#include <vector>

const int OFFSET_RECTANGLE_WORD = 10;
const int OFFSET_CIRCLE_WORD = 7;
const int OFFSET_LINE_WORD = 5;
const int OFFSET_POLYGON_WORD = 8;
const int OFFSET_ERASE_WORD = 6;
const int OFFSET_TRANSLATE_WORD = 10;

const int INSERT_COMMAND_FIRST_LETTER_OF_SHAPE_LOCATION = 7;
const int SPACE_ASCII = 32;
const int AMOUNT_WHITESPACE_COMMAND_RECTANGLE = 6;
const int AMOUNT_WHITESPACE_COMMAND_CIRCLE = 5;
const int AMOUNT_WHITESPACE_COMMAND_LINE = 6;

const char FIRST_LETTER_RECTANGLE = 'r';
const char FIRST_LETTER_CIRCLE = 'c';
const char FIRST_LETTER_LINE = 'l';
const char FIRST_LETTER_POLYGON = 'p';
const char FIRST_LETTER_VERTICAL = 'v';
const char FIRST_LETTER_HORIZONTAL = 'h';

class SVGContainer
{
private:
	
	int itemCount;
	
	std::vector<BaseShape*> shapes;

	void printRectangle(const BaseShape*) const;
	void printCircle(const BaseShape*) const;
	void printLine(const BaseShape*) const;
	void printPolygon(const BaseShape*) const;
	
	bool checkIfIntIsInInterval(const int, const std::pair<int, int>);

	bool checkIfPointIsWithinRectangle(const Rectangle&, const point&);

	bool checkIfRectangleIsWithinRectangle(const Rectangle&, const BaseShape&);

	bool checkIfCircleIsWithinRectangle(const Rectangle&, const BaseShape&);

	bool checkIfLineIsWithinRectangle(const Rectangle&, const BaseShape&);

	bool checkIfPolygonIsWithinRectangle(const Rectangle&, const BaseShape&);

	bool checkIfPointIsWithinCircle(const Circle&, const point&);

	bool checkIfRectangleIsWithinCircle(const Circle&, const BaseShape&);

	bool checkIfCircleIsWithinCircle(const Circle&, const BaseShape&);

	bool checkIfLineIsWithinCircle(const Circle&, const BaseShape&);

	bool checkIfPolygonIsWithinCircle(const Circle&, const BaseShape&);

	double getDistanceBetweenTwoPoints(const point&, const point&);
	
	shape checkTypeOfShape(BaseShape*);

	Rectangle* createRectangleFromUserInput(const std::string);
	Circle* createCircleFromUserInput(const std::string);
	Line* createLineFromUserInput(const std::string);
	Polygon* createPolygonFromUserInput(const std::string);
	
public:
	
	SVGContainer();
	SVGContainer(const std::vector<BaseShape*>); 
	SVGContainer(const SVGContainer&);
	SVGContainer& operator=(const SVGContainer&);

	void printShapes();
	void printShapes(int); 
	void createShape(const std::string);
	void eraseShape(const int);
	void eraseShape(const std::string);
	 
	void translateShape(const std::string); 
	
	bool figureWithingARectanglePassedAsAnObject(const Rectangle&, const BaseShape&);
	bool figureWithingACirclePassedAsAnObject(const Circle&, const BaseShape&); 

	void figureWithingCommand(const std::string); //TO BE REFACTORED

	void openFromContainer(const std::vector <std::string>);
	BaseShape* getItem(const int) const;
	int getCount() const;

	


	~SVGContainer();
};
