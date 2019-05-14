//
// Created by lyubo on 04.05.19.
//

#include <string>
#include "Headers/CommandLineInterface.h"
#include "Headers/StringManip.h"

Rectangle* CommandLineInterface::createRectangleFromUserInput(const std::string& userInput)
{
    int indexOfWordRectangle = userInput.find("rectangle");
    if (indexOfWordRectangle != -1)
    {
        double xCoordinate, yCoordinate, width, height;
        std::string color;

        std::string inputWithoutRectangle = userInput.substr(indexOfWordRectangle + OFFSET_RECTANGLE_WORD); //We erase everything behind the <x> coordinate => r:=<x> <y> <width> <height> <color>

        xCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, " ");
        yCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, " ");
        width = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, " ");
        height = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, " ");
        color = cutFirstSubstringFromString(inputWithoutRectangle, " ");

        //Pushes the item to the vector
        point p(xCoordinate, yCoordinate);
        Rectangle* result = new Rectangle(&p, color, width, height);

        return result;
    }
    else
    {
        std::cout << "Error !";
        return nullptr;
    }

}

Circle* CommandLineInterface::createCircleFromUserInput(const std::string& userInput)
{
    int indexOfWordCircle = userInput.find("circle");
    if (indexOfWordCircle != -1)
    {
        double xCoordinate, yCoordinate, radius;
        std::string color;

        std::string inputWithoutCircle = userInput.substr(indexOfWordCircle + OFFSET_CIRCLE_WORD); //We erase everything behind the <x> coordinate => r:=<x> <y> <width> <height> <color>

        xCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutCircle, " ");
        yCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutCircle, " ");
        radius = cutFirstNumberFromStringAsDouble(inputWithoutCircle, " ");
        color = cutFirstSubstringFromString(inputWithoutCircle, " ");

        point p(xCoordinate, yCoordinate);
        Circle* result = new Circle(&p, color, radius);

        return result;

    }
    else
    {
        std::cout << "Error !";
        return nullptr;
    }
}

Line* CommandLineInterface::createLineFromUserInput(const std::string& userInput)
{
    int indexOfWordLine = userInput.find("line");
    if (indexOfWordLine != 1)
    {
        double x1, y1, x2, y2;
        std::string color;

        std::string inputWithoutLine = userInput.substr(indexOfWordLine + OFFSET_LINE_WORD); //We erase everything behind the <x> coordinate => r:=<x> <y> <width> <height> <color>

        x1 = cutFirstNumberFromStringAsDouble(inputWithoutLine, " ");
        y1 = cutFirstNumberFromStringAsDouble(inputWithoutLine, " ");

        x2 = cutFirstNumberFromStringAsDouble(inputWithoutLine, " ");
        y2 = cutFirstNumberFromStringAsDouble(inputWithoutLine, " ");
        color = cutFirstSubstringFromString(inputWithoutLine, " ");

        //Pushes the item to the vector
        point* p = new point[2];
        point p1(x1, y1);
        point p2(x2, y2);
        p[0] = p1;
        p[1] = p2;

        Line* result = new Line(p, color);
        return result;
    }
}
Polygon* CommandLineInterface::createPolygonFromUserInput(const std::string& userInput)
{
    int indexOfWordPolygon = userInput.find("polygon");
    if (indexOfWordPolygon != 1)
    {
        std::string inputWithoutPolygon = userInput.substr(indexOfWordPolygon + OFFSET_POLYGON_WORD), color;
        int amountOfPoints = countChar(inputWithoutPolygon, SPACE_ASCII) - 1; //We also have one ' ' for the color

        double  x, y;

        if (amountOfPoints % 2 == 0)
        {
            point* p = new point[amountOfPoints / 2];
            for (int i = 0; i < amountOfPoints / 2; i++)
            {
                x = cutFirstNumberFromStringAsDouble(inputWithoutPolygon, " ");
                y = cutFirstNumberFromStringAsDouble(inputWithoutPolygon, " ");
                p[i] = point(x, y);
            }
            color = cutFirstSubstringFromString(inputWithoutPolygon, " ");

            Polygon* result = new Polygon(p, amountOfPoints / 2, color);

            return result;
        }
        else
        {
            std::cout << "Invalid command\n";
        }

        return nullptr;
    }
}

void CommandLineInterface::createShape(const std::string& userInput)
{
    //If the command is in this function, it contains create
    //User input format:
    //create <figure> <points> <additionalPoints> <color>

    //<rectangle> := create rectangle <x> <y> <width> <height> <color>
    //<circle> := create circle <x> <y> <r> <color>
    //<line> := create line <x1> <y1> <x2> <y2> <color>
    //<polygon> := create polygon <point1> <point2> ... <pointN> <color>

    //create rectangle 1000 1000 10 20 yellow

    if (userInput[INSERT_COMMAND_FIRST_LETTER_OF_SHAPE_LOCATION] == FIRST_LETTER_RECTANGLE)
    {
        if (countChar(userInput, SPACE_ASCII) < AMOUNT_WHITESPACE_COMMAND_RECTANGLE)
        {
            std::cout << "Invalid command\n";
        }
        else
        {
            Rectangle* temp = createRectangleFromUserInput(userInput);
            shapes.addShape(temp);
        }

    }
    else if (userInput[INSERT_COMMAND_FIRST_LETTER_OF_SHAPE_LOCATION] == FIRST_LETTER_CIRCLE)
    {
        if (countChar(userInput, SPACE_ASCII) < AMOUNT_WHITESPACE_COMMAND_CIRCLE)
        {
            std::cout << "Invalid command\n";
        }
        else
        {
            Circle* temp = createCircleFromUserInput(userInput);
            shapes.addShape(temp);
        }
    }
    else if (userInput[INSERT_COMMAND_FIRST_LETTER_OF_SHAPE_LOCATION] == FIRST_LETTER_LINE)
    {
        if (countChar(userInput, SPACE_ASCII) < AMOUNT_WHITESPACE_COMMAND_LINE)
        {
            std::cout << "Invalid command\n";
        }
        else
        {
            Line* temp = createLineFromUserInput(userInput);
            shapes.addShape(temp);
        }
    }
    else if (userInput[INSERT_COMMAND_FIRST_LETTER_OF_SHAPE_LOCATION] == FIRST_LETTER_POLYGON)
    {
        Polygon* temp = createPolygonFromUserInput(userInput);
        shapes.addShape(temp);
    }
    else
    {
        std::cout << "Error with command!";
        return;
    }
}
void CommandLineInterface::eraseShape(const std::string& userInput)
{
    int indexOfWordErase = userInput.find("erase");
    shapes.eraseShape(std::stoi(userInput.substr(indexOfWordErase + OFFSET_ERASE_WORD)));
}

void CommandLineInterface::translateShape(const std::string& coordinates)
{
    //translate vertical=10 horizontal=100
    //translate 1 vertical=20 horizontal=200

    int indexOfWordTranslate = coordinates.find("translate");
    int idOfFigureToTranslate = -1;
    double vertical, horizontal;
    std::string inputWithoutTranslate = coordinates.substr(indexOfWordTranslate + OFFSET_TRANSLATE_WORD); //removes translate

    if (inputWithoutTranslate[0] != FIRST_LETTER_VERTICAL)
    {
        //Input has id
        idOfFigureToTranslate = cutFirstNumberFromStringAsInt(inputWithoutTranslate, " ");
    }

    inputWithoutTranslate = removeWordFromString("vertical=", inputWithoutTranslate);
    vertical = cutFirstNumberFromStringAsDouble(inputWithoutTranslate, " ");

    inputWithoutTranslate = removeWordFromString("horizontal=", inputWithoutTranslate);
    horizontal = cutFirstNumberFromStringAsDouble(inputWithoutTranslate, " ");

    if (idOfFigureToTranslate == -1) //If we have to translate all figures, we loop them
    {
        int s = shapes.getCount();
        for (int i = 0; i < s; i++)
        {
            shapes.translateShape(i,vertical, horizontal);
        }
    }
    else
    {
        shapes.translateShape(idOfFigureToTranslate, vertical, horizontal);
    }
}

void CommandLineInterface::figureWithingCommand(const std::string& userInput) //TO BE REFACTORED
{
    //within circle 0 0 5

    //within rectangle <x> <y> <w> <h>
    //within circle <x> <y> <r>

    std::string inputWithoutWithin = removeFirstSubstringFromString(userInput, " ");

    if (inputWithoutWithin[0] == FIRST_LETTER_RECTANGLE)
    {
        int results = 0;
        Rectangle bound = *createRectangleFromUserInput(inputWithoutWithin);

        for (int i = 0; i < shapes.getCount(); i++)
        {
            if (figureWithingARectanglePassedAsAnObject(bound, *shapes[i]))
            {
                shapes.printShapes(i);
                results++;
            }
        }
        if (results == 0)
        {
            std::cout << "No figures are located " << userInput;
        }
    }
    else if(inputWithoutWithin[0] == FIRST_LETTER_CIRCLE)
    {
        Circle bound = *createCircleFromUserInput(inputWithoutWithin);
        int results = 0;
        for (int i = 0; i < shapes.getCount(); i++)
        {
            if (figureWithingACirclePassedAsAnObject(bound, *shapes[i]))
            {
                shapes.printShapes(i);
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

        return;
    }
}
void CommandLineInterface::openFromContainer(const std::vector<std::string>& containerWithCommandsAsString)
{
    for (const std::string& input : containerWithCommandsAsString)
    {
        createShape(input);
    }
}