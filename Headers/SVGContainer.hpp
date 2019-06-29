#pragma once
#include "Headers/Base.hpp"
#include "Headers/Rectangle.hpp"
#include "Headers/Line.hpp"
#include "Headers/Circle.hpp"

#include "Headers/MathFunctions.hpp"

#include "Headers/StringManip.hpp"
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
public:
	
	/*
	The container should generally be able to do the following things:
		- keep the shapes
		- add a shape
		- access a shape
		- print them
		- remove a shape
	    - translate a shape
	*/

	static SVGContainer& getInstance();

	void addShape(BaseShape*);

	void printShapes();
	void printShapes(int);

	void eraseShape(const int);

    void translateShape(const int&, const double&, const double&);

	const BaseShape * getItem(const int) const;
	const int getCount() const;

private:

    SVGContainer() {}
    SVGContainer(const SVGContainer&) = delete;
    SVGContainer& operator=(const SVGContainer&) = delete;

    int itemCount;
    std::vector<BaseShape*> shapes;

    //Wrapper for getType()
    const shape checkTypeOfShape(BaseShape *);

};
