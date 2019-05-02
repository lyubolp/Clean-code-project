#include "SVGFile.h"
#include "StringManip.cpp"
#include <iostream>
#include <fstream>


bool SVGFile::isValidLineRectangle(std::string line)
{
	int xf, yf, wf, hf, cf; //We make sure the line has all attributes

	xf = line.find("x=");
	yf = line.find("y=");
	wf = line.find("width=");
	hf = line.find("height=");
	cf = line.find("fill=");

	return (xf == -1 || yf == -1 || wf == -1 || hf == -1 || cf == -1);
}

bool SVGFile::isValidLineCircle(std::string line)
{
	int xf, yf, rf, cf;

	xf = line.find("cx=");
	yf = line.find("cy=");
	rf = line.find("r=");
	cf = line.find("fill=");

	return (xf == -1 || yf == -1 || rf == -1 || cf == -1);
}

bool SVGFile::isValidLineLine(std::string line)
{
	int x1f, y1f, x2f, y2f, cf;

	x1f = line.find("x1=");
	y1f = line.find("y1=");
	x2f = line.find("x2=");
	y2f = line.find("y2=");

	cf = line.find("fill=");

	return  (x1f == -1 || y1f == -1 || x2f == -1 || y2f == -1 || cf == -1);
}

std::string SVGFile::convertLineFromFileToCommandRectangle(std::string line)
{
	double x, y, width, heigth;
	std::string color, parsedString, lineCut;
	
	if (isValidLineRectangle(line))
	{
		lineCut = removeWordFromString("<rect", line);
		lineCut = removeBrackets(lineCut);
		lineCut = removeBlankSpaces(lineCut);

		while (lineCut.compare(">") != 0) //We get those attributes and save them, then we remove them from the line
		{
			int locationOfEquals = lineCut.find("=");

			if (lineCut[locationOfEquals - 1] == 'x')
			{
				lineCut = removeWordFromString("x=", lineCut);
				x = cutFirstNumberFromStringAsDouble(lineCut, "\"");
			}
			else if (lineCut[locationOfEquals - 1] == 'y')
			{
				lineCut = removeWordFromString("y=", lineCut);
				y = cutFirstNumberFromStringAsDouble(lineCut, "\"");
			}
			else if (lineCut[locationOfEquals - 1] == 'h')
			{
				lineCut = removeWordFromString("width=", lineCut);
				width = cutFirstNumberFromStringAsDouble(lineCut, "\"");
			}
			else if (lineCut[locationOfEquals - 1] == 't')
			{
				lineCut = removeWordFromString("height=", lineCut);
				heigth = cutFirstNumberFromStringAsDouble(lineCut, "\"");
			}
			else if (lineCut[locationOfEquals - 1] == 'l')
			{
				lineCut = removeWordFromString("fill=", lineCut);
				color = cutFirstSubstringFromString(lineCut, "\"");
			}
			else
			{
				std::cout << "Error";
				return "Error";
			}
		}
		parsedString = "create rectangle " + std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(width)
			+ ' ' + std::to_string(heigth) + ' ' + color; //Then we make the command to make the object

		return parsedString;
	}
	else
	
	{
		std::cout << "Not a valid line...\n";
		return "Not a valid line...\n";
	}
}

std::string SVGFile::convertLineFromFileToCommandCircle(std::string line)
{
	if (isValidLineCircle(line))
	{
		double x, y, radius;

		std::string color, parsedString, lineCut;

		lineCut = removeWordFromString("<circle", line);
		lineCut = removeBrackets(lineCut);
		lineCut = removeBlankSpaces(lineCut);

		while (lineCut.compare(">") != 0)
		{
			int locationOfEquals = lineCut.find("=");

			if (lineCut[locationOfEquals - 1] == 'x')
			{
				lineCut = removeWordFromString("cx=", lineCut);	
				x = cutFirstNumberFromStringAsDouble(lineCut, "\"");
			}
			else if (lineCut[locationOfEquals - 1] == 'y')
			{
				lineCut = removeWordFromString("cy=", lineCut);
				y = cutFirstNumberFromStringAsDouble(lineCut, "\"");
			}
			else if (lineCut[locationOfEquals - 1] == 'r')
			{
				lineCut = lineCut = removeWordFromString("r=", lineCut);
				radius = cutFirstNumberFromStringAsDouble(lineCut, "\"");

			}
			else if (lineCut[locationOfEquals - 1] == 'l')
			{
				lineCut = removeWordFromString("fill=", lineCut);
				color = cutFirstSubstringFromString(lineCut, "\"");
			}
			else
			{
				std::cout << "Error";
				return "Error";
			}
		}

		parsedString = "create circle " + std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(radius)
			+ ' ' + color;

		return parsedString;
	}
	else
	{
		std::cout << "Not a valid line...\n";
		return "Not a valid line...\n";
	}
}

std::string SVGFile::convertLineFromFileToCommandLine(std::string line)
{
	if (isValidLineLine(line))
	{
		double x, y, x2, y2;

		std::string color, parsedString, lineCut;

		lineCut = removeWordFromString("<line", line);
		lineCut = removeBrackets(lineCut);
		lineCut = removeBlankSpaces(lineCut);

		while (lineCut.compare(">") != 0)
		{
			int locationOfEquals = lineCut.find("=");

			if (lineCut[locationOfEquals - 2] == 'x' && lineCut[locationOfEquals - 1] == '1')
			{
				lineCut = removeWordFromString("x1=", lineCut);
				x = cutFirstNumberFromStringAsDouble(lineCut, "\"");
			}
			else if (lineCut[locationOfEquals - 2] == 'y' && lineCut[locationOfEquals - 1] == '1')
			{
				lineCut = removeWordFromString("y1=", lineCut);
				y = cutFirstNumberFromStringAsDouble(lineCut, "\"");
			}
			else if (lineCut[locationOfEquals - 2] == 'x' && lineCut[locationOfEquals - 1] == '2')
			{
				lineCut = removeWordFromString("x2=", lineCut);
				x2 = cutFirstNumberFromStringAsDouble(lineCut, "\"");
			}
			else if (lineCut[locationOfEquals - 2] == 'y' && lineCut[locationOfEquals - 1] == '2')
			{
				lineCut = removeWordFromString("y2=", lineCut);
				y2 = cutFirstNumberFromStringAsDouble(lineCut, "\"");
			}
			else if (lineCut[locationOfEquals - 1] == 'l')
			{
				lineCut = removeWordFromString("fill=", lineCut);
				color = cutFirstSubstringFromString(lineCut, "\"");
			}
		}

		parsedString = "create line " + std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(x2)
			+ ' ' + std::to_string(y2) + ' ' + color;

		return parsedString;
		
	}
	else
	{
		std::cout << "Not a valid line...\n";
		return "Not a valid line... \n";
	}
}

std::string SVGFile::convertLineFromFileToCommandPolygon(std::string line)
{
	std::string pointsString;
	//We don't know how many points are there, but we now that there in this format
	//x1,y1 x2,y2 x3,y3 etc...
	//but we can remove the commas and send it to the vector
	std::string color, parsedString, lineCut = line.substr(line.find("<polygon"));

	while (lineCut.compare(">") != 0)
	{
		if (removeBlankSpaces(lineCut).compare(">") == 0) break;
		int indexOfEquals = lineCut.find("=");

		if (lineCut[indexOfEquals - 1] == 'l')
		{
			lineCut = removeWordFromString("fill=", lineCut);
			color = cutFirstSubstringFromString(lineCut, "\"");
		}
		else if (lineCut[indexOfEquals - 1] == 's')
		{
			lineCut = removeBrackets(lineCut);
			lineCut = removeWordFromString("points=", lineCut);
			lineCut = replaceAll(lineCut, ',', ' ');
			pointsString = cutFirstSubstringFromString(lineCut, "\"");
		}
	}
	parsedString = "create polygon " + replaceAll(pointsString, ',', ' ') + ' ' + color;

	return parsedString;

}

std::string SVGFile::convertRectangleObjectToLine(const BaseShape * objectToConvert)
{
	std::string lineForFile(tags[1]);
	point pointOfShape = *objectToConvert->getPoints();
	
	lineForFile += concatenateTwoStrings(" x=\"", std::to_string(pointOfShape.x));
	lineForFile += concatenateTwoStrings("\" y=\"", std::to_string(pointOfShape.y));
	lineForFile += concatenateTwoStrings("\" width=\"", std::to_string(objectToConvert->getAdditionalPoints().x));
	lineForFile += concatenateTwoStrings("\" height=\"", std::to_string(objectToConvert->getAdditionalPoints().y));
	lineForFile += concatenateTwoStrings("\" fill=\"", objectToConvert->getColor());
	lineForFile += "\" />";

	return lineForFile;
}

std::string SVGFile::convertCircleObjectToLine(const BaseShape * objectToConvert)
{
	std::string lineForFile(tags[2]);
	point pointOfShape = *objectToConvert->getPoints();

	lineForFile += concatenateTwoStrings(" cx=\"", std::to_string(pointOfShape.x));
	lineForFile += concatenateTwoStrings("\" cy=\"", std::to_string(pointOfShape.y));
	lineForFile += concatenateTwoStrings("\" r=\"", std::to_string(objectToConvert->getAdditionalPoints().x));
	lineForFile += concatenateTwoStrings("\" fill=\"", objectToConvert->getColor());
	lineForFile += "\" />";

	return lineForFile;

}

std::string SVGFile::convertLineObjectToLine(const BaseShape * objectToConvert)
{
	std::string lineForFile(tags[3]);

	lineForFile += concatenateTwoStrings(" x1=\"", std::to_string(objectToConvert->getPoints()[0].x));
	lineForFile += concatenateTwoStrings("\" y1=\"", std::to_string(objectToConvert->getPoints()[0].y));
	lineForFile += concatenateTwoStrings("\" x2=\"", std::to_string(objectToConvert->getPoints()[1].x));
	lineForFile += concatenateTwoStrings("\" y2=\"", std::to_string(objectToConvert->getPoints()[1].y));

	lineForFile += concatenateTwoStrings("\" fill=\"", objectToConvert->getColor());
	lineForFile += "\" />";

	return lineForFile;
	
}

std::string SVGFile::convertPolygonObjectToLine(const BaseShape * currentObject)
{
	std::string lineForFile(tags[4]);

	lineForFile.append(" points=\"");

	int amountOfPoints = currentObject->getPointsCount();
	for (int i = 0; i < amountOfPoints - 1; i++)
	{
		lineForFile += concatenateTwoStrings(std::to_string(currentObject->getPoints()[i].x), ",");
		lineForFile += concatenateTwoStrings(std::to_string(currentObject->getPoints()[i].y)," ");
	}
	lineForFile += std::to_string(currentObject->getPoints()[amountOfPoints - 1].x);
	lineForFile += concatenateTwoStrings(",", std::to_string(currentObject->getPoints()[amountOfPoints - 1].y));
	lineForFile += concatenateTwoStrings("\" fill=\"", currentObject->getColor());
	lineForFile += "\"/>";

	return lineForFile;
}

void SVGFile::addFirstTagsToFile()
{
	fileWrite << firstLine << "\n";
	fileWrite << secondLine << "\n";
	fileWrite << tags[0] << "\n";
}

void SVGFile::addLineToFile(std::string lineToAdd)
{
	fileWrite << lineToAdd << "\n";
}

SVGFile::SVGFile()
{
}


int SVGFile::openFile(const std::string userInput)
{
	//open C:\Temp\file.xml
	//open <path>

	std::string filePathNotValidated, line, color, parsedString;

	filePathNotValidated = removeFirstSubstringFromString(userInput, " ");
	fileStream.open(filePathNotValidated);

	if (fileStream.is_open())
	{
		filePath = filePathNotValidated;

		std::string lineCut;
		while (getline(fileStream, line)) //We get each line and check the tag name
		{
			if (line.find("<rect") != -1)
			{
				parsedLines.push_back(convertLineFromFileToCommandRectangle(line));
			}
			else if (line.find("<circle") != -1) //The same is done for the circle
			{
				parsedLines.push_back(convertLineFromFileToCommandCircle(line));
			} 
			else if (line.find("<line") != -1) //And the line
			{
				parsedLines.push_back(convertLineFromFileToCommandLine(line));	
			}
			else if (line.find("<polygon") != -1)
			{	
				parsedLines.push_back(convertLineFromFileToCommandPolygon(line));
			}
			else
			{
				std::cout << "Invalid line";
				return 0;
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


int SVGFile::saveFile(const SVGContainer& shapesContainer)
{
	fileWrite.open(filePath, std::ofstream::trunc);
		
	if (fileWrite.is_open()) //We start writting to the file
	{
		addFirstTagsToFile();

		BaseShape* currentObject = new BaseShape();
		int amountOfShape = shapesContainer.getCount();

		for (int i = 0; i < amountOfShape; i++) //We loop all objects in the container
		{
			currentObject = shapesContainer.getItem(i);
			
			shape typeOfShape = currentObject->getType();

			if(typeOfShape == RectangleT)
			{
				std::string lineForFile = convertRectangleObjectToLine(currentObject);
				addLineToFile(lineForFile);
			}
			else if(typeOfShape == CircleT)
			{
				std::string lineForFile = convertCircleObjectToLine(currentObject);
				addLineToFile(lineForFile);
			}
			else if (typeOfShape == LineT)
			{
				std::string lineForFile = convertLineObjectToLine(currentObject);
				addLineToFile(lineForFile);
			}
			else if (typeOfShape == PolygonT)
			{
				std::string lineForFile = convertPolygonObjectToLine(currentObject);
				addLineToFile(lineForFile);
			}
			else
			{
				std::cout << "Error";
				return -1;
			}
		}
		addLineToFile(tags[6]);
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

int SVGFile::saveAsFile(const std::string userInput, const SVGContainer& containerWhichWillBeSaved)
{
	int startPositionOfTheCommand = userInput.find("saveas");
	std::string tempPath = filePath;
	filePath = userInput.substr(startPositionOfTheCommand + 7);
	filePath = removeChar(filePath, '"');
	std::cout << filePath << " ";

	saveFile(containerWhichWillBeSaved);

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
