#include "SVGFile.h"
#include "StringManip.h"
#include <iostream>
#include <fstream>


SVGFile::SVGFile()
{
}

int SVGFile::openFile(const std::string userInput)
{
	//open C:\Temp\file.xml
	//open <path>

	int f = userInput.find(" ");
	double x, y, x2, y2, w, h, radius;
	std::string r = userInput.substr(f + 1), line, color, parsedString;
	fileStream.open(r);

	if (fileStream.is_open())
	{
		filePath = r;
		while (getline(fileStream, line)) //We get each line and check the tag name
		{
			if (line.find("<rect") != -1)
			{
				int xf, yf, wf, hf, cf; //We make sure the line has all attributes

				xf = line.find("x=");
				yf = line.find("y=");
				wf = line.find("width=");
				hf = line.find("height=");
				cf = line.find("fill=");
				

				if (xf == -1 || yf == -1 || wf == -1 || hf == -1 || cf == -1)
				{
					std::cout << "Not a valid line...\n";
				}
				else
				{
					f = line.find("<rect");
					r = line.substr(f + 6);
					r = removeBrackets(r);
					r = removeBlankSpaces(r);

					while (r.compare(">") != 0) //We get those attributes and save them, then we remove them from the line
					{
						f = r.find("=");
						//depending on the type of the attribute
						if (r[f - 1] == 'x')
						{
							f = r.find("x=");
							r = r.substr(f + 3);
							f = r.find('"');
							x = std::stod(r.substr(0, f));
							r = r.substr(f + 1);
						}
						else if (r[f - 1] == 'y')
						{
							f = r.find("y=");
							r = r.substr(f + 3);
							f = r.find('"');
							y = std::stod(r.substr(0, f));
							r = r.substr(f + 1);
						}
						else if (r[f - 1] == 'h')
						{
							f = r.find("width=");
							r = r.substr(f + 7);
							f = r.find('"');
							w = std::stod(r.substr(0, f));
							r = r.substr(f + 1);
						}
						else if (r[f - 1] == 't')
						{
							f = r.find("height=");
							r = r.substr(f + 8);
							f = r.find('"');
							h = std::stod(r.substr(0, f));
							r = r.substr(f + 1);
						}
						else if (r[f - 1] == 'l')
						{
							f = r.find("fill=");
							r = r.substr(f + 6);
							f = r.find('"');
							color = r.substr(0, f);
							r = r.substr(f + 1);
						}
					}
					parsedString = "create rectangle " + std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(w)
						+ ' ' + std::to_string(h) + ' ' + color; //Then we make the command to make the object

					parsedLines.push_back(parsedString);
				}
				
			}
			else if (line.find("<circle") != -1) //The same is done for the circle
			{
				int xf, yf, rf, cf;

				xf = line.find("cx=");
				yf = line.find("cy=");
				rf = line.find("r=");
				cf = line.find("fill=");


				if (xf == -1 || yf == -1 || rf == -1 || cf == -1)
				{
					std::cout << "Not a valid line...\n";
					
				}
				else
				{
					f = line.find("<circle");
					r = line.substr(f + 8);
					r = removeBrackets(r);
					r = removeBlankSpaces(r);

					while (r.compare(">") != 0)
					{
						f = r.find("=");

						if (r[f - 1] == 'x')
						{
							f = r.find("cx=");
							r = r.substr(f + 4);
							f = r.find('"');
							x = std::stod(r.substr(0, f));
							r = r.substr(f + 1);
						}
						else if (r[f - 1] == 'y')
						{
							f = r.find("cy=");
							r = r.substr(f + 4);
							f = r.find('"');
							y = std::stod(r.substr(0, f));
							r = r.substr(f + 1);
						}
						else if (r[f - 1] == 'r')
						{
							f = r.find("r=");
							r = r.substr(f + 3);
							f = r.find('"');
							radius = std::stod(r.substr(0, f));
							r = r.substr(f + 1);
						}
						else if (r[f - 1] == 'l')
						{
							f = r.find("fill=");
							r = r.substr(f + 6);
							f = r.find('"');
							color = r.substr(0, f);
							r = r.substr(f + 1);
						}
					}

					parsedString = "create circle " + std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(radius)
						+ ' ' + color;

					parsedLines.push_back(parsedString);
				}
				
			} 
			else if (line.find("<line") != -1) //And the line
			{
				int x1f, y1f, x2f, y2f, cf;

				x1f = line.find("x1=");
				y1f = line.find("y1=");
				x2f = line.find("x2=");
				y2f = line.find("y2=");

				cf = line.find("fill=");


				if (x1f == -1 || y1f == -1 || x2f == -1 || y2f == -1 || cf == -1)
				{
					std::cout << "Not a valid line...\n";
				}
				else
				{
					f = line.find("<line");
					r = line.substr(f + 6);
					r = removeBrackets(r);
					r = removeBlankSpaces(r);

					while (r.compare(">") != 0)
					{
						f = r.find("=");

						if (r[f - 2] == 'x' && r[f - 1] == '1')
						{
							f = r.find("x1=");
							r = r.substr(f + 4);
							f = r.find('"');
							x = std::stod(r.substr(0, f));
							r = r.substr(f + 1);
						}
						else if (r[f - 2] == 'y' && r[f - 1] == '1')
						{
							f = r.find("y1=");
							r = r.substr(f + 4);
							f = r.find('"');
							y = std::stod(r.substr(0, f));
							r = r.substr(f + 1);
						}
						else if (r[f - 2] == 'x' && r[f - 1] == '2')
						{
							f = r.find("x2=");
							r = r.substr(f + 4);
							f = r.find('"');
							x2 = std::stod(r.substr(0, f));
							r = r.substr(f + 1);
						}
						else if (r[f - 2] == 'y' && r[f - 1] == '2')
						{
							f = r.find("y2=");
							r = r.substr(f + 4);
							f = r.find('"');
							y2 = std::stod(r.substr(0, f));
							r = r.substr(f + 1);
						}
						else if (r[f - 1] == 'l')
						{
							f = r.find("fill=");
							r = r.substr(f + 6);
							f = r.find('"');
							color = r.substr(0, f);
							r = r.substr(f + 1);
						}
					}

					parsedString = "create line " + std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(x2)
						+ ' ' + std::to_string(y2) + ' ' + color;

					parsedLines.push_back(parsedString);
				}

				
			}
			else if (line.find("<polygon") != -1)
			{
				std::string pointsString;
				//We don't know how many points are there, but we now that there in this format
				//x1,y1 x2,y2 x3,y3 etc...
				//but we can remove the commas and send it to the vector
				r = line.substr(line.find("<polygon"));

				while (r.compare(">") != 0)
				{
					if (removeBlankSpaces(r).compare(">") == 0) break;
					f = r.find("=");

					if (r[f - 1] == 'l')
					{
						f = r.find("fill=");
						r = r.substr(f + 6);
						f = r.find('"');
						color = r.substr(0, f);
						r = r.substr(f + 1);
					}
					else if (r[f - 1] == 's')
					{
						r = removeBrackets(r);
						f = r.find("points=");
						r = r.substr(f + 8);
						r = replaceAll(r, ',', ' ');
						f = r.find('"');
						pointsString = r.substr(0, f);
						r = r.substr(f+1);
					}
				}
				parsedString = "create polygon " + replaceAll(pointsString, ',', ' ') + ' ' + color;

				parsedLines.push_back(parsedString);


			}
		}
		
		fileStream.close();
	}
	else
	{
		std::cout << "File cannot be opened\n";
		return 0;
	}
	return 1;
}


int SVGFile::saveFile(const SVGContainer& rhs)
{
	BaseShape* curObj = new BaseShape();
	int s = rhs.getCount();
	fileWrite.open(filePath, std::ofstream::trunc);
	std::string lineToAdd;
	point p;
	if (fileWrite.is_open()) //We start writting to the file
	{
		//We add the first lines
		fileWrite << firstLine << "\n";
		fileWrite << secondLine << "\n";
		fileWrite << tags[0] << "\n";
		for (int i = 0; i < s; i++) //We loop all objects in the container
		{
			curObj = rhs.getItem(i);
			p = *(curObj->getPoints());
			switch (curObj->getType()) //We check the type
			{
			case RectangleT: //We write the SVG
				lineToAdd = "";
				lineToAdd += tags[1];
				lineToAdd.append(" x=\"");
				lineToAdd += std::to_string(p.x);
				lineToAdd.append("\" y=\""); 
				lineToAdd += std::to_string(p.y);
				lineToAdd.append("\" width=\"");
				lineToAdd += std::to_string(curObj->getAdditionalPoints().x);
				lineToAdd.append("\" height=\"");
				lineToAdd += std::to_string(curObj->getAdditionalPoints().y);
				lineToAdd.append("\" fill=\"");
				lineToAdd += curObj->getColor();
				lineToAdd.append("\" />");
				fileWrite << lineToAdd << "\n";
				break;
			case CircleT:
				lineToAdd = "";
				lineToAdd += tags[2];
				lineToAdd.append(" cx=\"");
				lineToAdd += std::to_string(p.x);
				lineToAdd.append("\" cy=\"");
				lineToAdd += std::to_string(p.y);
				lineToAdd.append("\" r=\"");
				lineToAdd += std::to_string(curObj->getAdditionalPoints().x);
				lineToAdd.append("\" fill=\"");
				lineToAdd += curObj->getColor();
				lineToAdd.append("\" />");
				fileWrite << lineToAdd << "\n";
				break;
			case LineT:
				lineToAdd = "";
				lineToAdd += tags[3];
				lineToAdd.append(" x1=\"");
				lineToAdd += std::to_string(curObj->getPoints()[0].x);
				lineToAdd.append("\" y1=\"");
				lineToAdd += std::to_string(curObj->getPoints()[0].y);
				lineToAdd.append("\" x2=\"");
				lineToAdd += std::to_string(curObj->getPoints()[1].x);
				lineToAdd.append("\" y2=\"");
				lineToAdd += std::to_string(curObj->getPoints()[1].y);

				lineToAdd.append("\" fill=\"");
				lineToAdd += curObj->getColor();
				lineToAdd.append("\" />");
				fileWrite << lineToAdd << "\n";
				break;
			case PolygonT:
			{
				lineToAdd = "";
				lineToAdd += tags[4];
				lineToAdd.append(" points=\"");
				int s = curObj->getPointsCount();
				for (int i = 0; i < s-1; i++)
				{
					lineToAdd += std::to_string(curObj->getPoints()[i].x);
					lineToAdd.append(",");
					lineToAdd += std::to_string(curObj->getPoints()[i].y);
					lineToAdd.append(" ");
				}
				lineToAdd += std::to_string(curObj->getPoints()[s-1].x);
				lineToAdd.append(",");
				lineToAdd += std::to_string(curObj->getPoints()[s-1].y);

				lineToAdd.append("\" fill=\"");
				lineToAdd += curObj->getColor();
				lineToAdd.append("\"/>");
				fileWrite << lineToAdd << "\n";
				break;
			}
			default:
				std::cout << "Error \n";
				break;
			}
		}
		fileWrite << tags[6] << "\n";
		fileWrite.close();
	}
	else
	{
		std::cout << "Error opening file...\n";
	}
	return 1;
}
std::string SVGFile::getFileName() const
{
	return filePath;
}

int SVGFile::saveAsFile(const std::string userInput, const SVGContainer& rhs)
{
	int f = userInput.find("saveas");
	std::string tempPath = filePath;
	filePath = userInput.substr(f + 7);
	filePath = removeChar(filePath, '"');
	std::cout << filePath << " ";

	saveFile(rhs);

	filePath = tempPath;
	return 1;
}

int SVGFile::closeFile()
{
	fileStream.close();
	fileWrite.close();
	filePath = "";
	return 0;
}



std::vector<std::string> SVGFile::loadIntoContainer() const
{
	return parsedLines;
}
