#pragma once
#include "Base.h"
#include "Rectangle.h"
#include "Polygon.h"
#include "Line.h"
#include "Circle.h"
#include <vector>

class SVGContainer
{
private:
	std::vector<BaseShape*> items;
	int itemCount;
public:
	
	SVGContainer();
	SVGContainer(const std::vector<BaseShape*>); //Makes an SVGContainer with a 
	SVGContainer(const SVGContainer&);
	SVGContainer& operator=(const SVGContainer&);

	void printShapes();
	void printShapes(int);
	void createShape(const std::string); //TO BE REFACTORED
	void eraseShape(const int);
	void eraseShape(const std::string);
	 
	void translateShape(const std::string); //TO BE REFACTORED
	
	bool figureWithingARectangleOrCirclePassedAsAnObject(const Rectangle&, const BaseShape&) const; //TO BE REFACTORED
	bool figureWithingARectangleOrCirclePassedAsAnObject(const Circle&, const BaseShape&) const; //TO BE REFACTORED

	void figureWithingARectangleOrCircle(const std::string); //TO BE REFACTORED

	void openFromContainer(const std::vector <std::string>);
	BaseShape* getItem(const int) const;
	int getCount() const;

	


	~SVGContainer();
};
