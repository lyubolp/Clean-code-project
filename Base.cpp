#include "Base.h"
#include <cstring>
Base::Base()
{
	points = new point[0];
	pointsCount = 0;

	color = new char[1];
	color = '\0';
	type = Default;
}
Base::Base(const point* p, const int pc, const std::string c, const figure t):color(c), type(t), pointsCount(pc)
{
	points = new point[pc];

	for (int i = 0; i < pc; i++)
	{
		points[i] = p[i];
	}
}
Base::Base(const Base& rhs) :color(rhs.color), type(rhs.type), pointsCount(rhs.pointsCount)
{
	
	points = new point[rhs.pointsCount];
	for (int i = 0; i < rhs.pointsCount; i++)
	{
		points[i] = rhs.points[i];
	}
}
Base& Base::operator=(const Base& rhs)
{
	if (this != &rhs)
	{
		color = rhs.color;

		delete[] points;
		points = new point[rhs.pointsCount];
		for (int i = 0; i < rhs.pointsCount; i++)
		{
			points[i] = rhs.points[i];
		}
		type = rhs.type;
		pointsCount = rhs.pointsCount;

	}
	return *this;
}

void Base::setType(const figure t)
{
	type = t;
}
void Base::setPointCount(const int pc)
{
	pointsCount = pc;
}
void Base::setColor(const std::string c)
{
	color = c;
}
figure Base::getType() const
{
	return type;
}
point* Base::getPoints() const
{
	return points;
}
int Base::getPointsCount() const
{
	return pointsCount;
}
std::string Base::getColor() const
{
	return color;
}

void Base::setPoints(const point rhs, int n) //Sets a point based on point number (1-n), where n is the number of points;
{
	//This needs to be optimized
	//This is an abstract function
	point* newPoints = new point[pointsCount];

	for (int i = 0; i < n-1; i++)
	{
	newPoints[i] = points[i];
	}
	newPoints[n-1] = rhs;
	for (int i = n; i < pointsCount; i++)
	{
	newPoints[i] = points[i];
	}

	delete[] points;
	points = newPoints;
}
void Base::setPoints(const double xn, const double yn, int n)
{
	//This needs to be optimized
	//This is an abstract function
	
	point* newPoints = new point[pointsCount];

	for (int i = 0; i < n - 1; i++)
	{
	newPoints[i] = points[i];
	}
	newPoints[n - 1].x = xn;
	newPoints[n - 1].y = yn;
	for (int i = n; i < pointsCount; i++)
	{
	newPoints[i] = points[i];
	}

	delete[] points;
	points = newPoints;
}
void Base::setPoints(const point* p, const int pc) //All points
{
	//This needs to be optimized


	delete[] points;
	points = new point[pc];

	for (int i = 0; i < pc; i++)
	{
		points[i] = p[i];
	}

	pointsCount = pc;
}

void Base::translate(const int v, const int h)
{
	for (int i = 0; i < pointsCount; i++)
	{
		points[i].x += h;
		points[i].y += v;
	}
}

point Base::getAdditionalPoints() const
{
	return point(0, 0);
}

void Base::setSize(const point)
{
}

Base::~Base()
{
	delete[] points;
}
std::ostream& operator<<(std::ostream& os, point p)
{
	os << p.x << " " << p.y;
	return os;
}