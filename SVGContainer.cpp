#include "SVGContainer.h"
#include "StringManip.h"
#include <iostream>
#include <cmath>

SVGContainer::SVGContainer() :itemCount(0)
{
	//items = new Base[0];
}
SVGContainer::SVGContainer(const std::vector<BaseShape*> rhs) : itemCount(1)
{
	items = rhs;
}
SVGContainer::SVGContainer(const SVGContainer& rhs)
{
	items = rhs.items;
	itemCount = rhs.itemCount;
}
SVGContainer& SVGContainer::operator=(const SVGContainer& rhs)
{
	if (this != &rhs)
	{
		items = rhs.items;
		itemCount = rhs.itemCount;
	}
	return *this;
}
void SVGContainer::print(int id)
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

	point* p; //We get the points of the current object
	std::cout << id + 1 << ". "; //Prints the id-s
	p = items[id]->getPoints(); //Get the points
	if (items[id]->getType() == RectangleT) //We check the type of the figure & we print the data
	{
		std::cout << "rectangle " << *items[id]->getPoints() << " " << items[id]->getAdditionalPoints() << " " << items[id]->getColor() << "\n"; //THIS MAY NOT WORK
	}
	if (items[id]->getType() == CircleT)
	{
		std::cout << "circle " << *items[id]->getPoints() << " " << items[id]->getAdditionalPoints().x << " " << items[id]->getColor() << "\n";
	}
	if (items[id]->getType() == LineT)
	{
		std::cout << "line " << p[0] << " " << p[1] << " " << items[id]->getColor() << "\n";
	}
	if (items[id]->getType() == PolygonT)
	{
		std::cout << "polygon ";
		int pc = items[id]->getPointsCount();
		
		for (int i = 0; i < pc; i++) //The polygon has an unknown amount of points
		{
			std::cout << p[i] << " ";
		}
		std::cout<< items[id]->getColor() << "\n";
	}
}
void SVGContainer::print()
{
	//If we want to print all objects, we just make a loop
	for (int i = 0; i < itemCount; i++)
	{
		print(i);
	}
}

void SVGContainer::create(const std::string userInput)
{
	//If the command is in this function, it contains create
	//User input format:
	//create <figure> <points> <additionalPoints> <color>

	//<rectangle> := create rectangle <x> <y> <width> <height> <color>
	//<circle> := create circle <x> <y> <r> <color>
	//<line> := create line <x1> <y1> <x2> <y2> <color>
	//<polygon> := create polygon <point1> <point2> ... <pointN> <color>

	//create rectangle 1000 1000 10 20 yellow
	
	int f;
	itemCount++;
	
	if (userInput[7] == 'r')
	{
		if (countChar(userInput, ' ') < 6 || countChar(userInput, 32) < 6)
		{
			std::cout << "Invalid command\n";
		}
		else
		{
			f = userInput.find("rectangle");
			if (f != -1)
			{
				double x, y, w, h;
				std::string color;

				//x start position is f+9

				std::string r = userInput.substr(f + 10); //We erase everything behind the <x> coordinate => r:=<x> <y> <width> <height> <color>

				//Gets <x>
				f = r.find(" ");
				x = std::stod(r.substr(0, f));
				r = r.substr(f + 1);

				//Gets <y>
				f = r.find(" ");
				y = std::stod(r.substr(0, f));
				r = r.substr(f + 1);

				//Gets <width>
				f = r.find(" ");
				w = std::stod(r.substr(0, f));
				r = r.substr(f + 1);

				//Gets <height>
				f = r.find(" ");
				h = std::stod(r.substr(0, f));
				r = r.substr(f + 1);

				//Gets color
				f = r.find(" ");
				color = r.substr(0, f);

				//Pushes the item to the vector
				point p(x, y);
				Rectangle* temp = new Rectangle(&p, color, w, h);

				items.push_back(temp);
			}
		}
		
	}
	else if (userInput[7] == 'c')
	{
		if (countChar(userInput, ' ') < 5 || countChar(userInput, 32) < 5)
		{
			std::cout << "Invalid command\n";
		}
		else
		{
			f = userInput.find("circle");
			if (f != -1)
			{
				double x, y;
				double radius;
				std::string color;

				//x start position is f+8

				std::string r = userInput.substr(f + 7); //We erase everything behind the <x> coordinate => r:=<x> <y> <width> <height> <color>

				//Gets <x>
				f = r.find(" ");
				x = std::stod(r.substr(0, f));
				r = r.substr(f + 1);

				//Gets <y>
				f = r.find(" ");
				y = std::stod(r.substr(0, f));
				r = r.substr(f + 1);

				//Gets <r>
				f = r.find(" ");
				radius = std::stod(r.substr(0, f));
				r = r.substr(f + 1);

				//Gets color
				f = r.find(" ");
				color = r.substr(0, f);

				//Pushes the item to the vector
				point p(x, y);
				Circle* temp = new Circle(&p, color, radius);
				items.push_back(temp);

			}
		}
	}
	else if (userInput[7] == 'l')
	{
		if (countChar(userInput, ' ') < 6 || countChar(userInput, 32) < 6)
		{
			std::cout << "Invalid command\n";
		}
		else
		{
			f = userInput.find("line");
			if (f != 1)
			{
				double x1, y1, x2, y2;
				std::string color;

				//x start position is f+8

				std::string r = userInput.substr(f + 5); //We erase everything behind the <x> coordinate => r:=<x> <y> <width> <height> <color>

				//Gets <x1>
				f = r.find(" ");
				x1 = std::stod(r.substr(0, f));
				r = r.substr(f + 1);

				//Gets <y1>
				f = r.find(" ");
				y1 = std::stod(r.substr(0, f));
				r = r.substr(f + 1);

				//Gets <x2>
				f = r.find(" ");
				x2 = std::stod(r.substr(0, f));
				r = r.substr(f + 1);

				//Gets <y2>
				f = r.find(" ");
				y2 = std::stod(r.substr(0, f));
				r = r.substr(f + 1);

				//Gets color
				f = r.find(" ");
				color = r.substr(0, f);

				//Pushes the item to the vector
				point* p = new point[2];
				point p1(x1, y1);
				point p2(x2, y2);
				p[0] = p1;
				p[1] = p2;

				Line* temp = new Line(p, color);
				items.push_back(temp);
			}
		}
	}
	else if (userInput[7] == 'p')
	{	
			f = userInput.find("polygon");
			if (f != 1)
			{
				std::string r = userInput.substr(f + 8), temp = r, color;
				int n = -1, s = temp.size(); //amount of coordinates
				double  x, y;
				for (int i = 0; i < s; i++)
				{
					f = temp.find(" ");
					temp = temp.substr(f + 1);
					n++;
					if (f == -1) break;
					s -= f;
				}
				if (n % 2 == 0) //We also have one ' ' for the color
				{
					point* p = new point[n / 2];
					for (int i = 0; i < n / 2; i++)
					{
						//Gets <x>
						f = r.find(" ");
						x = std::stod(r.substr(0, f));
						r = r.substr(f + 1);

						//Gets <y>
						f = r.find(" ");
						y = std::stod(r.substr(0, f));
						r = r.substr(f + 1);

						p[i] = point(x, y);
					}
					//Gets color
					f = r.find(" ");
					color = r.substr(0, f);

					Polygon* temp = new Polygon(p, n / 2, color);

					items.push_back(temp);
				}
				else
				{
					std::cout << "Invalid command\n";
				}
			}
	}
}
void SVGContainer::erase(const int id)
{
	if (id <= itemCount) //If the figure exists
	{
		std::vector<BaseShape*>::iterator it = items.begin(); 
		items.erase(it + (id - 1)); //We find the one we need to delete
		std::cout << "Deleted successfully  figure " << id << "\n";
		itemCount--;
	}
	else 
	{
		std::cout << "There is no figure " << id << "\n";
	}
}

void SVGContainer::erase(const std::string userInput)
{
	int f = userInput.find("erase");
	erase(std::stoi(userInput.substr(f + 6)));
}

void SVGContainer::translate(const std::string coordinates)
{
	//translate vertical=10 horizontal=100
	//translate 1 vertical=20 horizontal=200

	int f = coordinates.find("translate");
	int id = -1;
	double vertical, horizontal;
	std::string r = coordinates.substr(f + 10); //removes translate 
	//leaves only:<id> vertical=<x> horizontal=<y>


	if (r[0] != 'v')
	{
		//Input has id
		f = r.find(" "); 
		id = std::stod(r.substr(0, f));
		r = r.substr(f + 1);
	}

	f = r.find("vertical=");
	r = r.substr(f + 9);
	f = r.find(" ");

	vertical = std::stod(r.substr(0, f));

	r = r.substr(f + 1); //next is horizontal=<y>
	f = r.find("horizontal=");
	r = r.substr(f + 11);
	f = r.find(" ");

	horizontal = std::stod(r.substr(0, f));
	
	if (id == -1) //If we have to translate all figures, we loop them
	{
		int s = items.size();
		for (int i = 0; i < s; i++)
		{
			items[i]->translate(vertical, horizontal); 
		}
	}
	else
	{
		items[id]->translate(vertical, horizontal);//If we have 1 figure, we translate it
	}
	
}
bool SVGContainer::within_s(const Rectangle& bound, const BaseShape & obj) const
{
	point* boundPoint = bound.getPoints();
	int pc = obj.getPointsCount();

	point objPoint = *obj.getPoints();
	if (obj.getType() == RectangleT)
	{
		//If the rectangle has 4 points - A(x,y), B(x+w,y), C(x,y+h), D(x+w, y+h)
		//We must check all of them

		//A
		if (objPoint.x < boundPoint->x) return false;
		if (objPoint.x >(boundPoint->x + bound.getAdditionalPoints().x)) return false;
		if (objPoint.y < boundPoint->y) return false;
		if (objPoint.y > (boundPoint->y + bound.getAdditionalPoints().y)) return false;

		//D (x & y are different)
		if ((objPoint.x + obj.getAdditionalPoints().x) < boundPoint->x) return false;
		if ((objPoint.x + obj.getAdditionalPoints().x) > (boundPoint->x + bound.getAdditionalPoints().x)) return false;
		if ((objPoint.y + obj.getAdditionalPoints().y) < boundPoint->y) return false;
		if ((objPoint.y + obj.getAdditionalPoints().y) > (boundPoint->y + bound.getAdditionalPoints().y)) return false;
	}
	else if (obj.getType() == CircleT)
	{
		//The circle has 5 points of collision - O(x,y), A(x+r,y), B(x-r,y), C(x,y+r), D(x,y-r)

		//0
		if (objPoint.x < boundPoint->x) return false;
		if (objPoint.x >(boundPoint->x + bound.getAdditionalPoints().x)) return false;
		if (objPoint.y < boundPoint->y) return false;
		if (objPoint.y >(boundPoint->y + bound.getAdditionalPoints().y)) return false;

		//A(y is the same)
		if ((objPoint.x + obj.getAdditionalPoints().x) < boundPoint->x) return false;
		if ((objPoint.x + obj.getAdditionalPoints().x) > (boundPoint->x + bound.getAdditionalPoints().x)) return false;

		//B(y is the same)
		if ((objPoint.x - obj.getAdditionalPoints().x) < boundPoint->x) return false;
		if ((objPoint.x - obj.getAdditionalPoints().x) > (boundPoint->x + bound.getAdditionalPoints().x)) return false;

		//C(x is the same)
		if ((objPoint.y + obj.getAdditionalPoints().x) < boundPoint->y) return false;
		if ((objPoint.y + obj.getAdditionalPoints().x) > (boundPoint->y + bound.getAdditionalPoints().y)) return false;

		//D(x is the same)
		if ((objPoint.y - obj.getAdditionalPoints().x) < boundPoint->y) return false;
		if ((objPoint.y - obj.getAdditionalPoints().x) > (boundPoint->y + bound.getAdditionalPoints().y)) return false;
	}
	else if (obj.getType() == LineT)
	{
		for (int i = 0; i < pc; i++)
		{
			if (objPoint.x < (boundPoint+i)->x) return false;
			if (objPoint.x >((boundPoint + i)->x + bound.getAdditionalPoints().x)) return false;
			if (objPoint.y < boundPoint->y) return false;
			if (objPoint.y >(boundPoint->y + bound.getAdditionalPoints().y)) return false;
		}
	}
	else if (obj.getType() == PolygonT)
	{
		for (int i = 0; i < pc; i++)
		{
			if (objPoint.x < (boundPoint + i)->x) return false;
			if (objPoint.x >((boundPoint + i)->x + bound.getAdditionalPoints().x)) return false;
			if (objPoint.y < boundPoint->y) return false;
			if (objPoint.y >(boundPoint->y + bound.getAdditionalPoints().y)) return false;
		}
	}
	return true;
}
bool SVGContainer::within_s(const Circle & bound, const BaseShape & obj) const
{
	point* boundPoint = bound.getPoints();
	int pc = obj.getPointsCount();
	double radius = bound.getAdditionalPoints().x;
	point objPoint = *obj.getPoints();


	if (obj.getType() == RectangleT)
	{
		//we check the farthest point of the rectangle if its inside the circle
		//We do this with the formula: x^2 + y^2 <= r^2

		//left point of rectangle (x,y)
		if ((pow((boundPoint->x - objPoint.x),2) + pow((boundPoint->y - objPoint.y),2)) > pow(radius,2)) return false;

		//right point of rectangle (x+w, y)
		if ((pow((boundPoint->x - (objPoint.x + obj.getAdditionalPoints().x)),2) + pow((boundPoint->y - objPoint.y),2)) > pow(radius,2)) return false;
		
		//bottom left point (x, y+h)
		if ((pow((boundPoint->x - objPoint.x), 2) + pow(boundPoint->y - (objPoint.y + obj.getAdditionalPoints().y), 2) ) > pow(radius, 2)) return false;

		//bottom right poit (x+w, y+h)
		if (pow((boundPoint->x - (objPoint.x + obj.getAdditionalPoints().x)),2) + pow(boundPoint->y - (objPoint.y + obj.getAdditionalPoints().y),2) > pow(radius,2)) return false;
	}
	else if (obj.getType() == CircleT)
	{
		double distanceFromCenter = -1;
		distanceFromCenter = sqrt((abs((int)(boundPoint->x - objPoint.x)))^2 + (abs((int)(boundPoint->y - objPoint.y))) ^ 2); //We check if the distance from center is smaller than the radius

		if ((distanceFromCenter + obj.getAdditionalPoints().x) > radius) return false;
	}
	else if (obj.getType() == LineT)
	{
		for (int i = 0; i < pc; i++)
		{
			if ((pow(((boundPoint+i)->x - objPoint.x),2 ) + pow(((boundPoint+i)->y - objPoint.y),2)) > pow(radius,2)) return false;
		}
	}
	else if (obj.getType() == PolygonT)
	{
		for (int i = 0; i < pc; i++)
		{
			if ((pow(((boundPoint + i)->x - objPoint.x),2) + pow(((boundPoint + i)->y - objPoint.y),2)) > radius ^ 2) return false;
		}
	}
	return true;
}
void SVGContainer::within(const std::string userInput)
{
	//within circle 0 0 5

	//within rectangle <x> <y> <w> <h>
	//within circle <x> <y> <r>
	int f = userInput.find(" ");
	std::string r = userInput.substr(f + 1);

	if (r[0] == 'r')
	{

		double x, y, w, h;
		std::string color;

		//x start position is f+10

		std::string r = userInput.substr(f + 11); //We erase everything behind the <x> coordinate => r:=<x> <y> <width> <height> <color>

		//Gets <x>
		f = r.find(" ");
		x = std::stod(r.substr(0, f));
		r = r.substr(f + 1);

		//Gets <y>
		f = r.find(" ");
		y = std::stod(r.substr(0, f));
		r = r.substr(f + 1);

		//Gets <width>
		f = r.find(" ");
		w = std::stod(r.substr(0, f));
		r = r.substr(f + 1);

		//Gets <height>
		f = r.find(" ");
		h = std::stod(r.substr(0, f));
		r = r.substr(f + 1);

		point* tempPoint = new point(x,y);
		Rectangle t(tempPoint, "white", w, h);
		int results = 0;
		for (int i = 0; i < itemCount; i++)
		{
			if (within_s(t, *items[i]))
			{
				print(i);
				results++;
			}
		}
		if (results == 0)
		{
			std::cout << "No figures are located " << userInput;
		}
	}
	else if(r[0] == 'c')
	{
		double x, y, radius;
		std::string color;

		//x start position is f+10

		std::string r = userInput.substr(f + 8); //We erase everything behind the <x> coordinate => r:=<x> <y> <width> <height> <color>

		//Gets <x>
		f = r.find(" ");
		x = std::stod(r.substr(0, f));
		r = r.substr(f + 1);

		//Gets <y>
		f = r.find(" ");
		y = std::stod(r.substr(0, f));
		r = r.substr(f + 1);

		//Gets <radius>
		f = r.find(" ");
		radius = std::stod(r.substr(0, f));
		r = r.substr(f + 1);

		point* tempPoint = new point(x,y);
		Circle t(tempPoint, "white", radius);
		int results = 0;
		for (int i = 0; i < itemCount; i++)
		{
			if (within_s(t, *items[i]))
			{
				print(i);
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
	}
}

void SVGContainer::openFromContainer(const std::vector<std::string> rhs)
{
	for (std::string input : rhs)
	{
		create(input);
	}
}

BaseShape* SVGContainer::getItem(const int id) const
{
	return items[id];
}

int SVGContainer::getCount() const
{
	return itemCount;
}



SVGContainer::~SVGContainer()
{
	int s = items.size();
	for (int i = 0; i < s; i++)
	{
		delete items[i];
	}
}
 