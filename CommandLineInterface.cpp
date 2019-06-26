//
// Created by lyubo on 04.05.19.
//

#include <string>
#include <cstring>
#include "Headers/CommandLineInterface.h"
#include "Headers/StringManip.h"


CommandLineInterface::CommandLineInterface()
{
    isFileOpen = false;
}
void CommandLineInterface::fillPointsFromUserInput(point *toFill, int &amountOfPoints, std::string &inputWtihoutPolygon)
{
    if(amountOfPoints % 2 != 0)
    {
        throw std::length_error("Invalid amount of points");
    }
    double x = 0, y = 0;
    for(int i = 0; i < amountOfPoints / 2; i++)
    {
        x = cutFirstNumberFromStringAsDouble(inputWtihoutPolygon, ' ');
        y = cutFirstNumberFromStringAsDouble(inputWtihoutPolygon, ' ');
        if(x == std::numeric_limits<double>::min() || y == -std::numeric_limits<double>::min())
        {
            throw std::invalid_argument("Invalid user input");
        }
        toFill[i] = point(x, y);
    }
}

Rectangle *CommandLineInterface::createRectangleFromUserInput(const std::string &userInput)
{
    int indexOfWordRectangle = userInput.find("rectangle");
    if(indexOfWordRectangle != std::string::npos)
    {
        std::string inputWithoutRectangle = userInput.substr(indexOfWordRectangle +
                                                             OFFSET_RECTANGLE_WORD);

        double xCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, ' ');
        double yCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, ' ');
        double width = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, ' ');
        double height = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, ' ');

        if(xCoordinate == std::numeric_limits<double>::min() || yCoordinate == std::numeric_limits<double>::min()
           || width == std::numeric_limits<double>::min() || height == std::numeric_limits<double>::min())
        {
            throw std::invalid_argument("Invalid input");
        }

        std::string color = cutFirstSubstringFromString(inputWithoutRectangle, ' ');

        if(color == invalidDelimiter)
        {
            throw std::invalid_argument(invalidDelimiter);
        }

        point p(xCoordinate, yCoordinate);
        Rectangle *result = new Rectangle(&p, color, width, height);

        return result;
    }
    else
    {
        throw std::invalid_argument("Invalid input");
    }

}

Circle *CommandLineInterface::createCircleFromUserInput(const std::string &userInput)
{
    int indexOfWordCircle = userInput.find("circle");
    if(indexOfWordCircle != std::string::npos)
    {
        std::string inputWithoutCircle = userInput.substr(indexOfWordCircle +
                                                          OFFSET_CIRCLE_WORD);

        double xCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutCircle, ' ');
        double yCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutCircle, ' ');
        double radius = cutFirstNumberFromStringAsDouble(inputWithoutCircle, ' ');

        if(xCoordinate == std::numeric_limits<double>::min() || yCoordinate == std::numeric_limits<double>::min()
           || radius == std::numeric_limits<double>::min())
        {
            throw std::invalid_argument("Invalid input");
        }

        std::string color = cutFirstSubstringFromString(inputWithoutCircle, ' ');

        if(color == invalidDelimiter)
        {
            throw std::invalid_argument(invalidDelimiter);
        }

        point p(xCoordinate, yCoordinate);
        Circle *result = new Circle(&p, color, radius);

        return result;

    }
    else
    {
        throw std::invalid_argument("Invalid user input");
    }
}

Line *CommandLineInterface::createLineFromUserInput(const std::string &userInput)
{
    int indexOfWordLine = userInput.find("line");
    if(indexOfWordLine != 1)
    {
        std::string inputWithoutLine = userInput.substr(indexOfWordLine + OFFSET_LINE_WORD);

        double x1 = cutFirstNumberFromStringAsDouble(inputWithoutLine, ' ');
        double y1 = cutFirstNumberFromStringAsDouble(inputWithoutLine, ' ');

        double x2 = cutFirstNumberFromStringAsDouble(inputWithoutLine, ' ');
        double y2 = cutFirstNumberFromStringAsDouble(inputWithoutLine, ' ');

        if(x1 == std::numeric_limits<double>::min() || y1 == std::numeric_limits<double>::min()
        || x2 == std::numeric_limits<double>::min() || y2 == std::numeric_limits<double>::min())
        {
            throw std::invalid_argument(invalidDelimiter);
        }
        std::string color = cutFirstSubstringFromString(inputWithoutLine, ' ');

        if(color == invalidDelimiter)
        {
            throw std::invalid_argument(invalidDelimiter);
        }

        //Pushes the item to the vector
        auto *temp = new point[2];
        point first(x1, y1);
        point second(x2, y2);
        temp[0] = first;
        temp[1] = second;

        Line *result = new Line(temp, color);
        return result;
    }
    return nullptr;
}

Polygon *CommandLineInterface::createPolygonFromUserInput(const std::string &userInput)
{
    int indexOfWordPolygon = userInput.find("polygon");
    if(indexOfWordPolygon != 1)
    {
        std::string inputWithoutPolygon = userInput.substr(indexOfWordPolygon + OFFSET_POLYGON_WORD), color;
        int amountOfPoints = countChar(inputWithoutPolygon, SPACE_ASCII) - 1; //We also have one ' ' for the color

        if(amountOfPoints % 2 == 0)
        {
            auto *temp = new point[amountOfPoints / 2];
            try
            {
                fillPointsFromUserInput(temp, amountOfPoints, inputWithoutPolygon);
                color = cutFirstSubstringFromString(inputWithoutPolygon, ' ');

                if(color != invalidDelimiter)
                {
                    Polygon *result = new Polygon(temp, amountOfPoints / 2, color);
                    return result;
                }
            }
            catch(std::length_error& lengthError)
            {
                throw lengthError;
            }
            catch(std::invalid_argument& invalidArgument)
            {
                throw invalidArgument;
            }

        }
        else
        {
            throw std::invalid_argument("Invalid command\n");
        }
    }
    return nullptr;
}

bool CommandLineInterface::exec(const std::string &userInput)
{
    if(userInput.find("create") != std::string::npos)
    {
        try
        {
            createShape(userInput);
        }
        catch(std::invalid_argument& )
        {
                std::cout << "Error with command!";
                return false;
        }
    }
    else if(userInput.find("erase") != std::string::npos)
    {
        try
        {
            eraseShape(userInput);
        }
        catch(std::invalid_argument& e)
        {
            //std::cout << "Cannot erase shape\n";
            return false;
        }
    }
    else if(userInput.find("translate") != std::string::npos)
    {
        /*if(!translateShape(userInput))
        {
            std::cout << "Cannot translate shape\n";
            return false;
        }*/
    }
    else if(userInput.find("within") != std::string::npos)
    {
        /*if(!figureWithingCommand(userInput))
        {
            return false;
        }*/
    }
    else if(userInput.find("open") != std::string::npos)
    {
        file.openFile(userInput);
    }
    return true;
}

void CommandLineInterface::createShape(const std::string &userInput)
{
    //If the command is in this function, it contains create
    //User input format:
    //create <figure> <points> <additionalPoints> <color>

    //<rectangle> := create rectangle <x> <y> <width> <height> <color>
    //<circle> := create circle <x> <y> <r> <color>
    //<line> := create line <x1> <y1> <x2> <y2> <color>
    //<polygon> := create polygon <point1> <point2> ... <pointN> <color>

    //create rectangle 1000 1000 10 20 yellow

    if(userInput[INSERT_COMMAND_FIRST_LETTER_OF_SHAPE_LOCATION] == FIRST_LETTER_RECTANGLE)
    {
        if(countChar(userInput, SPACE_ASCII) < AMOUNT_WHITESPACE_COMMAND_RECTANGLE)
        {
            throw std::invalid_argument("Invalid command");
        }
        else
        {
            Rectangle *temp = createRectangleFromUserInput(userInput);
            shapes.addShape(temp);
        }

    }
    else if(userInput[INSERT_COMMAND_FIRST_LETTER_OF_SHAPE_LOCATION] == FIRST_LETTER_CIRCLE)
    {
        if(countChar(userInput, SPACE_ASCII) < AMOUNT_WHITESPACE_COMMAND_CIRCLE)
        {
            throw std::invalid_argument("Invalid command");
        }
        else
        {
            Circle *temp = createCircleFromUserInput(userInput);
            shapes.addShape(temp);
        }
    }
    else if(userInput[INSERT_COMMAND_FIRST_LETTER_OF_SHAPE_LOCATION] == FIRST_LETTER_LINE)
    {
        if(countChar(userInput, SPACE_ASCII) < AMOUNT_WHITESPACE_COMMAND_LINE)
        {
            throw std::invalid_argument("Invalid command");
        }
        else
        {
            Line *temp = createLineFromUserInput(userInput);
            shapes.addShape(temp);
        }
    }
    else if(userInput[INSERT_COMMAND_FIRST_LETTER_OF_SHAPE_LOCATION] == FIRST_LETTER_POLYGON)
    {
        Polygon *temp = createPolygonFromUserInput(userInput);
        shapes.addShape(temp);
    }
    else
    {
        throw std::invalid_argument("Invalid command");
    }
}

void CommandLineInterface::eraseShape(const std::string &userInput)
{

    int indexOfWordErase = userInput.find("erase");
    if(indexOfWordErase == std::string::npos)
    {
        throw std::invalid_argument("Invalid command");
    }
    shapes.eraseShape(std::stoi(userInput.substr(indexOfWordErase + OFFSET_ERASE_WORD)));
}

void CommandLineInterface::translateShape(const std::string &coordinates)
{
    //translate vertical=10 horizontal=100
    //translate 1 vertical=20 horizontal=200

    int indexOfWordTranslate = coordinates.find("translate");
    std::string inputWithoutTranslate = coordinates.substr(
            indexOfWordTranslate + OFFSET_TRANSLATE_WORD); //removes translate

    int idOfFigureToTranslate = -1;
    if(inputWithoutTranslate[0] != FIRST_LETTER_VERTICAL)
    {
        //Input has id
        idOfFigureToTranslate = cutFirstNumberFromStringAsInt(inputWithoutTranslate, ' ');
    }

    inputWithoutTranslate = removeWordFromString("vertical=", inputWithoutTranslate);
    double vertical = cutFirstNumberFromStringAsDouble(inputWithoutTranslate, ' ');

    inputWithoutTranslate = removeWordFromString("horizontal=", inputWithoutTranslate);
    double horizontal = cutFirstNumberFromStringAsDouble(inputWithoutTranslate, ' ');

    if(idOfFigureToTranslate == -1) //If we have to translate all figures, we loop them
    {
        int s = shapes.getCount();
        for(int i = 0; i < s; i++)
        {
            shapes.translateShape(i, vertical, horizontal);
        }
    }
    else
    {
        shapes.translateShape(idOfFigureToTranslate, vertical, horizontal);
    }
}

void CommandLineInterface::figureWithingCommand(const std::string &userInput)
{
    //within circle 0 0 5

    //within rectangle <x> <y> <w> <h>
    //within circle <x> <y> <r>

    std::string inputWithoutWithin = removeFirstSubstringFromString(userInput, ' ');

    if(inputWithoutWithin[0] == FIRST_LETTER_RECTANGLE)
    {
        int results = 0;
        Rectangle bound = *createRectangleFromUserInput(inputWithoutWithin);

        for(int i = 0; i < shapes.getCount(); i++)
        {
            if(shapes.figureWithingARectanglePassedAsAnObject(bound, *shapes.getItem(i)))
            {
                shapes.printShapes(i);
                results++;
            }
        }
        if(results == 0)
        {
            std::cout << "No figures are located " << userInput;
        }
    }
    else if(inputWithoutWithin[0] == FIRST_LETTER_CIRCLE)
    {
        Circle bound = *createCircleFromUserInput(inputWithoutWithin);
        int results = 0;
        for(int i = 0; i < shapes.getCount(); i++)
        {
            if(shapes.figureWithingACirclePassedAsAnObject(bound, *shapes.getItem(i)))
            {
                shapes.printShapes(i);
                results++;
            }
        }
        if(results == 0)
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

void CommandLineInterface::openFromContainer(const std::vector<std::string> &containerWithCommandsAsString)
{
    for(const std::string &input : containerWithCommandsAsString)
    {
        createShape(input);
    }
}