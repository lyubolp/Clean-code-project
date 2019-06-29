#include "Headers/SVGFile.hpp"
#include <iostream>
#include <fstream>

SVGFile& SVGFile::getInstance()
{
    static SVGFile instance;

    return instance;
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


const int SVGFile::openFile(const std::string & userInput)
{
    //open C:\Temp\file.xml
    //open <path>
    std::string filePathNotValidated = removeFirstSubstringFromString(userInput, ' ');
    fileStream.open(filePathNotValidated);

    if (fileStream.is_open())
    {
        filePath = filePathNotValidated; //After the file is successfully opened, then we can have a valid file
        std::string line("Invalid line");
        while (getline(fileStream, line)) //We get each line and check the tag name
        {
            try
            {
                convertLineFromFileToCommand(line);
            }
            catch(std::invalid_argument& e)
            {
                return 0;
            }
        }
        fileStream.close();
    }
    else
    {
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

        try
        {
            for (int i = 0; i < amountOfShape; i++) //We loop all objects in the container
            {
                currentObject = shapesContainer.getItem(i);
                convertObjectToLine(currentObject);
            }
            addLineToFile(tags[6]);
            fileWrite.close();
        }
        catch(std::exception& e)
        {
            throw e;
        }
    }
    else
    {
        throw std::runtime_error("Invalid file");
    }
    return 1;
}

int SVGFile::saveAsFile(const std::string userInput, const SVGContainer& containerWhichWillBeSaved)
{
    std::string tempPath = filePath;

    filePath = removeWordFromString("saveas", userInput);
    filePath = removeChar(filePath, '"');
    std::cout << filePath << " ";

    try
    {
        saveFile(containerWhichWillBeSaved);
    }
    catch(std::exception& e)
    {
        throw e;
    }

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


std::string SVGFile::getFileName() const
{
    return filePath;
}
std::vector<std::string> SVGFile::loadIntoContainer() const
{
    return parsedLines;
}

void SVGFile::convertLineFromFileToCommand(std::string& line)
{
    if (line.find("<rect") != -1)
    {
        try
        {
            parsedLines.push_back(convertLineFromFileToCommandRectangle(line));
        }
        catch(std::invalid_argument& e)
        {
            throw e;
        }
    }
    else if (line.find("<circle") != -1) //The same is done for the circle
    {
        try
        {
            parsedLines.push_back(convertLineFromFileToCommandCircle(line));
        }
        catch(std::invalid_argument& e)
        {
            throw e;
        }
    }
    else if (line.find("<line") != -1) //And the line
    {
        try
        {
            parsedLines.push_back(convertLineFromFileToCommandLine(line));
        }
        catch(std::invalid_argument& e)
        {
            throw e;
        }
    }
    else if (line.find("<polygon") != -1)
    {
        parsedLines.push_back(convertLineFromFileToCommandPolygon(line));
    }
    else
    {
        return;
    }

}

void SVGFile::convertObjectToLine(const BaseShape * currentObject) {


    shape typeOfShape = currentObject->getType();

    if(typeOfShape == RECTANGLE)
    {
        try
        {
            std::string lineForFile = convertRectangleObjectToLine(currentObject);
            addLineToFile(lineForFile);
        }
        catch(std::exception& e)
        {
            throw e;
        }
    }
    else if(typeOfShape == CIRCLE)
    {
        try
        {
            std::string lineForFile = convertCircleObjectToLine(currentObject);
            addLineToFile(lineForFile);
        }
        catch(std::exception& e)
        {
            throw e;
        }
    }
    else if (typeOfShape == LINE)
    {
        try
        {
            std::string lineForFile = convertLineObjectToLine(currentObject);
            addLineToFile(lineForFile);
        }
        catch(std::exception& e)
        {
            throw e;
        }

    }
    else if (typeOfShape == POLYGON)
    {
        try
        {
            std::string lineForFile = convertPolygonObjectToLine(currentObject);
            addLineToFile(lineForFile);
        }
        catch(std::exception& e)
        {
            throw e;
        }
    }
    else
    {
        std::cout << "Error";
        return;
    }
}
