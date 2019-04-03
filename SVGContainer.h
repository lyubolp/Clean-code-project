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
	std::vector<Base*> items;
	int itemCount;
public:
	
	SVGContainer();
	SVGContainer(const std::vector<Base*>); //Makes an SVGContainer with a 
	SVGContainer(const SVGContainer&);
	SVGContainer& operator=(const SVGContainer&);

	void print();
	void print(int);
	void create(const std::string);
	void erase(const int);
	void erase(const std::string);
	
	void translate(const std::string);
	
	bool within_s(const Rectangle&, const Base&) const;
	bool within_s(const Circle&, const Base&) const;

	void within(const std::string);

	void openFromContainer(const std::vector <std::string>);
	Base* getItem(const int) const;
	int getCount() const;

	


	~SVGContainer();
};
