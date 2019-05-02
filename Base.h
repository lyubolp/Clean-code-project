#pragma once
#include <iostream>
#include <string>
enum shape
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

class BaseShape
{
private:
	point * points; //Triangle has 1 point, Rectangle 1, Circle has 0, Line has 2
	int pointsCount; //Points count
	std::string color;
	shape shapeType; //Types are triangle, rectangle, circle, line

	//These two will definetly be moved to another class
	void deleteDynamicArray(point*);
	void replaceDynamicArray(point*,const point*, const int);
	void copyDynamicArray(point*, const point*, const int);
	point* insertObjectIntoArray(std::pair<point, const int>, std::pair<point*, const int>);
	
public:
	
	BaseShape();
	BaseShape(const point*, const int,const std::string, const shape);
	BaseShape(const BaseShape&);
	BaseShape& operator=(const BaseShape&);

	void setTypeOfShape(const shape);
	void setPointCount(const int);
	void setColor(const std::string);

	shape getType() const;
	std::string getColor() const;
	point* getPoints() const;
	int getPointsCount() const;

	void setPoints(const point, int); //Sets a point based on point number (1-n), where n is the number of points;
	void setPoints(const double, const double, int);
	void setPoints(const point*, const int); //All points
	void translate(const int, const int);

	virtual point getAdditionalPoints() const;
	virtual void setSize(const point);

	virtual ~BaseShape();
};

