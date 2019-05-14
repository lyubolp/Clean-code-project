//
// Created by lyubo on 14.05.19.
//

#ifndef CLEAN_CODE_PROJECT_INPUTPARSER_H
#define CLEAN_CODE_PROJECT_INPUTPARSER_H

#include <iostream>
#include <string.h>
#include "InputValidation.h"
#include "StringManip.h"
#include "Base.h"

std::string convertLineFromFileToCommandRectangle(std::string line)
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

std::string convertLineFromFileToCommandCircle(std::string line)
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

std::string convertLineFromFileToCommandLine(std::string line)
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

std::string convertLineFromFileToCommandPolygon(std::string line)
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

std::string convertRectangleObjectToLine(const BaseShape * objectToConvert)
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

std::string convertCircleObjectToLine(const BaseShape * objectToConvert)
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

std::string convertLineObjectToLine(const BaseShape * objectToConvert)
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

std::string convertPolygonObjectToLine(const BaseShape * currentObject)
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
#endif //CLEAN_CODE_PROJECT_INPUTPARSER_H
