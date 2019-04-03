#pragma once
#include <iostream>
#include <string>
enum figure
{
	RectangleT,
	CircleT,
	LineT,
	PolygonT,
	Default
};
struct point
{
	double x, y;
	point() {};
	point(double a, double b) :x(a), y(b) {};
};
std::ostream& operator<<(std::ostream& os, point p);

class Base
{
private:
	point * points; //Triangle has 1 point, Rectangle 1, Circle has 0, Line has 2
	int pointsCount; //Points count
	std::string color;
	figure type; //Types are triangle, rectangle, circle, line
public:
	
	Base();
	Base(const point*, const int,const std::string, const figure);
	Base(const Base&);
	Base& operator=(const Base&);

	void setType(const figure);
	void setPointCount(const int);
	void setColor(const std::string);

	figure getType() const;
	std::string getColor() const;
	point* getPoints() const;
	int getPointsCount() const;

	void setPoints(const point, int); //Sets a point based on point number (1-n), where n is the number of points;
	void setPoints(const double, const double, int);
	void setPoints(const point*, const int); //All points
	void translate(const int, const int);

	virtual point getAdditionalPoints() const;
	virtual void setSize(const point);

	virtual ~Base();
};

