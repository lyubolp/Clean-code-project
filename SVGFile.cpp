#include "Headers/SVGFile.h"
#include <iostream>
#include <fstream>

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


void SVGFile::convertLineFromFileToCommand(std::string line)
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
        std::cout << line;
        return;
    }

}

void SVGFile::convertObjectToLine(const BaseShape * currentObject) {


    shape typeOfShape = currentObject->getType();

    if(typeOfShape == RECTANGLE)
    {
        std::string lineForFile = convertRectangleObjectToLine(currentObject);
        addLineToFile(lineForFile);
    }
    else if(typeOfShape == CIRCLE)
    {
        std::string lineForFile = convertCircleObjectToLine(currentObject);
        addLineToFile(lineForFile);
    }
    else if (typeOfShape == LINE)
    {
        std::string lineForFile = convertLineObjectToLine(currentObject);
        addLineToFile(lineForFile);
    }
    else if (typeOfShape == POLYGON)
    {
        std::string lineForFile = convertPolygonObjectToLine(currentObject);
        addLineToFile(lineForFile);
    }
    else
    {
        std::cout << "Error";
        return;
    }
}
const int SVGFile::openFile(const std::string & userInput)
{
	//open C:\Temp\file.xml
	//open <path>

    std::string filePathNotValidated = removeFirstSubstringFromString(userInput, " ");
	fileStream.open(filePathNotValidated);

	if (fileStream.is_open())
	{
		filePath = filePathNotValidated;
        std::string line("Invalid line");
		while (getline(fileStream, line)) //We get each line and check the tag name
		{
            convertLineFromFileToCommand(line);
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

		const BaseShape* currentObject = new BaseShape();
		int amountOfShape = shapesContainer.getCount();

		for (int i = 0; i < amountOfShape; i++) //We loop all objects in the container
		{
			currentObject = shapesContainer.getItem(i);
            convertObjectToLine(currentObject);
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
    std::string tempPath = filePath;

	filePath = removeWordFromString(filePath, "saveas");
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
