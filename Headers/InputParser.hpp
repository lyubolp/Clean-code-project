//
// Created by lyubo on 14.05.19.
//

#ifndef CLEAN_CODE_PROJECT_INPUTPARSER_HPP
#define CLEAN_CODE_PROJECT_INPUTPARSER_HPP

#include <iostream>
#include <string.h>
#include "InputValidation.hpp"
#include "StringManip.hpp"
#include "Base.hpp"
#include "SVGFile.hpp"


static std::string firstLine = "<?xml version=\"1.0\" standalone=\"no\"?>";
static std::string secondLine = "<!DOCTYPE svg PUBLIC \" - //W3C//DTD SVG 1.1//EN\" \" http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd \"> ";
static std::string tags[7] = {"<svg>", "<rect", "<circle", "<line", "<polygon", "/>", "</svg>"};

inline const std::string convertLineFromFileToCommandRectangle(const std::string &line)
{
    //The function that converts XML to command for SVGContainer
    double x = -1, y = -1, width = -1, height = -1;
    std::string color, parsedString, lineCut;

    if(isValidLineRectangle(line))
    {
        lineCut = removeWordFromString("<rect", line);
        lineCut = removeBrackets(lineCut);
        lineCut = removeBlankSpaces(lineCut);

        for(int i = 0; i < 5; i++)
        {
            int locationOfEquals = lineCut.find('=');

            if(lineCut[locationOfEquals - 1] == 'x')
            {
                lineCut = removeWordFromString("x=", lineCut);

                try
                {
                    x = cutFirstNumberFromStringAsDouble(lineCut, '"');
                }
                catch(std::invalid_argument &e)
                {
                    throw e;
                }
            }
            else if(lineCut[locationOfEquals - 1] == 'y')
            {
                lineCut = removeWordFromString("y=", lineCut);

                try
                {
                    y = cutFirstNumberFromStringAsDouble(lineCut, '"');
                }
                catch(std::invalid_argument &e)
                {
                    throw e;
                }
            }
            else if(lineCut[locationOfEquals - 1] == 'h')
            {
                lineCut = removeWordFromString("width=", lineCut);
                try
                {
                    width = cutFirstNumberFromStringAsDouble(lineCut, '"');
                }
                catch(std::invalid_argument &e)
                {
                    throw e;
                }
            }
            else if(lineCut[locationOfEquals - 1] == 't')
            {
                lineCut = removeWordFromString("height=", lineCut);
                try
                {
                    height = cutFirstNumberFromStringAsDouble(lineCut, '"');
                }
                catch(std::invalid_argument &e)
                {
                    throw e;
                }
            }
            else if(lineCut[locationOfEquals - 1] == 'l')
            {
                lineCut = removeWordFromString("fill=", lineCut);
                try
                {
                    color = cutFirstSubstringFromString(lineCut, '"');
                }
                catch(std::invalid_argument &e)
                {
                    throw e;
                }
            }
            else
            {
                throw std::invalid_argument("Invalid input");
            }
        }
        parsedString = "create rectangle " + std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(width)
                       + ' ' + std::to_string(height) + ' ' + color; //Then we make the command to make the object

        return parsedString;
    }
    else
    {
        throw std::invalid_argument("Invalid input");
    }
}

inline std::string convertLineFromFileToCommandCircle(std::string line)
{
    //The function that converts XML to command for SVGContainer
    if(isValidLineCircle(line))
    {
        double x, y, radius;

        std::string color, parsedString, lineCut;

        lineCut = removeWordFromString("<circle", line);
        lineCut = removeBrackets(lineCut);
        lineCut = removeBlankSpaces(lineCut);

        for(int i = 0; i < 4; i++)
        {
            int locationOfEquals = lineCut.find("=");

            if(lineCut[locationOfEquals - 1] == 'x')
            {
                lineCut = removeWordFromString("cx=", lineCut);
                x = cutFirstNumberFromStringAsDouble(lineCut, '"');
            }
            else if(lineCut[locationOfEquals - 1] == 'y')
            {
                lineCut = removeWordFromString("cy=", lineCut);
                y = cutFirstNumberFromStringAsDouble(lineCut, '"');
            }
            else if(lineCut[locationOfEquals - 1] == 'r')
            {
                lineCut = lineCut = removeWordFromString("r=", lineCut);
                radius = cutFirstNumberFromStringAsDouble(lineCut, '"');

            }
            else if(lineCut[locationOfEquals - 1] == 'l')
            {
                lineCut = removeWordFromString("fill=", lineCut);
                color = cutFirstSubstringFromString(lineCut, '"');
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

inline std::string convertLineFromFileToCommandLine(std::string line)
{
    //The function that converts XML to command for SVGContainer
    if(isValidLineLine(line))
    {
        double x, y, x2, y2;

        std::string color, parsedString, lineCut;

        lineCut = removeWordFromString("<line", line);
        lineCut = removeBrackets(lineCut);
        lineCut = removeBlankSpaces(lineCut);

        for(int i = 0; i < 5; i++)
        {
            int locationOfEquals = lineCut.find("=");

            if(lineCut[locationOfEquals - 2] == 'x' && lineCut[locationOfEquals - 1] == '1')
            {
                lineCut = removeWordFromString("x1=", lineCut);
                x = cutFirstNumberFromStringAsDouble(lineCut, '"');
            }
            else if(lineCut[locationOfEquals - 2] == 'y' && lineCut[locationOfEquals - 1] == '1')
            {
                lineCut = removeWordFromString("y1=", lineCut);
                y = cutFirstNumberFromStringAsDouble(lineCut, '"');
            }
            else if(lineCut[locationOfEquals - 2] == 'x' && lineCut[locationOfEquals - 1] == '2')
            {
                lineCut = removeWordFromString("x2=", lineCut);
                x2 = cutFirstNumberFromStringAsDouble(lineCut, '"');
            }
            else if(lineCut[locationOfEquals - 2] == 'y' && lineCut[locationOfEquals - 1] == '2')
            {
                lineCut = removeWordFromString("y2=", lineCut);
                y2 = cutFirstNumberFromStringAsDouble(lineCut, '"');
            }
            else if(lineCut[locationOfEquals - 1] == 'l')
            {
                lineCut = removeWordFromString("fill=", lineCut);
                color = cutFirstSubstringFromString(lineCut, '"');
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

inline std::string convertLineFromFileToCommandPolygon(std::string line)
{
    //We don't know how many points are there, but we now that there in this format
    //x1,y1 x2,y2 x3,y3 etc...
    //but we can remove the commas and send it to the vector

    //<polygon points="200,10 250,190 160,210" fill="#0000FF"/>
    line = removeBrackets(line); //polygon points="200,10 250,190 160,210" fill="#0000FF"
    line = removeWordFromString("points=", line);
    line = removeWordFromString("fill=", line);
    line = removeChar(line, '"'); //polygon =200,10 250,190 160,210 =#0000FF
    line = replaceAll(line, ',', ' '); //polygon =200 10 250 190 160 210" #0000FF

    std::string points, color;
    return "create " + line;

}

inline std::string convertRectangleObjectToLine(const BaseShape *objectToConvert)
{
    //This converts an Rectangle object to XML
    std::string lineForFile(tags[1]);
    point pointOfShape = *objectToConvert->getPoints();

    try
    {
        lineForFile += concatenateTwoStrings(" x=\"", std::to_string(pointOfShape.x));
        lineForFile += concatenateTwoStrings("\" y=\"", std::to_string(pointOfShape.y));
        lineForFile += concatenateTwoStrings("\" width=\"", std::to_string(objectToConvert->getAdditionalPoints().x));
        lineForFile += concatenateTwoStrings("\" height=\"", std::to_string(objectToConvert->getAdditionalPoints().y));
        lineForFile += concatenateTwoStrings("\" fill=\"", objectToConvert->getColor());
        lineForFile += "\" />";
    }
    catch(std::exception& e)
    {
        throw e;
    }
    return lineForFile;
}

inline std::string convertCircleObjectToLine(const BaseShape *objectToConvert)
{
    //This converts an Circle object to XML
    std::string lineForFile(tags[2]);
    point pointOfShape = *objectToConvert->getPoints();

    try
    {
        lineForFile += concatenateTwoStrings(" cx=\"", std::to_string(pointOfShape.x));
        lineForFile += concatenateTwoStrings("\" cy=\"", std::to_string(pointOfShape.y));
        lineForFile += concatenateTwoStrings("\" r=\"", std::to_string(objectToConvert->getAdditionalPoints().x));
        lineForFile += concatenateTwoStrings("\" fill=\"", objectToConvert->getColor());
        lineForFile += "\" />";
    }
    catch(std::exception& e)
    {
        throw e;
    }
    return lineForFile;

}

inline std::string convertLineObjectToLine(const BaseShape *objectToConvert)
{
    //This converts an Line object to XML
    std::string lineForFile(tags[3]);

    try
    {
        lineForFile += concatenateTwoStrings(" x1=\"", std::to_string(objectToConvert->getPoints()[0].x));

        lineForFile += concatenateTwoStrings("\" y1=\"", std::to_string(objectToConvert->getPoints()[0].y));
        lineForFile += concatenateTwoStrings("\" x2=\"", std::to_string(objectToConvert->getPoints()[1].x));
        lineForFile += concatenateTwoStrings("\" y2=\"", std::to_string(objectToConvert->getPoints()[1].y));

        lineForFile += concatenateTwoStrings("\" fill=\"", objectToConvert->getColor());
        lineForFile += "\" />";
    }
    catch(std::exception& e)
    {
        throw e;
    }
    return lineForFile;

}

inline std::string convertPolygonObjectToLine(const BaseShape *currentObject)
{
    //This converts an Polygon object to XML
    std::string lineForFile(tags[4]);

    lineForFile.append(" points=\"");

    int amountOfPoints = currentObject->getPointsCount();

    try
    {
        for(int i = 0; i < amountOfPoints - 1; i++)
        {
            lineForFile += concatenateTwoStrings(std::to_string(currentObject->getPoints()[i].x), ",");
            lineForFile += concatenateTwoStrings(std::to_string(currentObject->getPoints()[i].y), " ");
        }
        lineForFile += std::to_string(currentObject->getPoints()[amountOfPoints - 1].x);
        lineForFile += concatenateTwoStrings(",", std::to_string(currentObject->getPoints()[amountOfPoints - 1].y));
        lineForFile += concatenateTwoStrings("\" fill=\"", currentObject->getColor());
        lineForFile += "\"/>";
    }
    catch(std::exception& e)
    {
        throw e;
    }
    return lineForFile;
}

#endif //CLEAN_CODE_PROJECT_INPUTPARSER_HPP
