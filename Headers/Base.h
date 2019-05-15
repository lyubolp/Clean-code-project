#pragma once
#include <iostream>
#include <string>
enum shape
{
	RECTANGLE,
	CIRCLE,
	LINE,
	POLYGON,
	DEFAULT
}; 
struct point
{
	double x, y;
	point() {};
	point(double a, double b) :x(a), y(b)
	{
		if (x < 0)
		{
			std::cout << "X is less than 0, setting it to 0. \n";
			x = 0;
		}
		if (y < 0)
		{
			std::cout << "Y is less than 0, setting it to 0. \n";
			y = 0;
		}
	}
}; 
std::ostream& operator<<(std::ostream& os, point p);

class BaseShape
{
private:
	point * points; //Triangle has 1 point, Rectangle 1, Circle has 0, Line has 2
	int pointsCount; //Points count
	std::string color;
	shape shapeType; //Types are triangle, rectangle, circle, line
	

public:
	
	BaseShape();
	BaseShape(const point*, const int,const std::string, const shape);
	BaseShape(const BaseShape&);
	BaseShape& operator=(const BaseShape&);

	void setTypeOfShape(const shape);
	void setPointCount(const int);
	void setColor(const std::string);

	const shape getType() const;
	const std::string getColor() const;
	const point * getPoints() const;
	const int getPointsCount() const;

	void setPoints(const point, int); //Sets a point based on point number (1-n), where n is the number of points;
	void setPoints(const double, const double, int);
	void setPoints(const point*, const int); //All points
	void translate(const int, const int);

	virtual const point getAdditionalPoints() const{return point(-1, -1);};
	virtual void setSize(const point) {};
    virtual void print() const {};

	virtual ~BaseShape();
};

