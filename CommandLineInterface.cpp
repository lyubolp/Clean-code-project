//
// Created by lyubo on 04.05.19.
//

#include <string>
#include <cstring>
#include "Headers/CommandLineInterface.hpp"
#include "Headers/StringManip.hpp"


CommandLineInterface::CommandLineInterface():isFileOpen(false)
{

}

Rectangle *CommandLineInterface::createRectangleFromUserInput(const std::string &userInput)
{
    //Turns <rect x="77.000000" y="73.000000" width="1.000000" height="1.000000" fill="#3399ff" />
    //into
    //create rectangle 77.000000 73.000000 1.000000 1.000000 #3399ff
    //That is due to the fact that the SVGContainer can parse commands to create a Rectangle object

    int indexOfWordRectangle = userInput.find("rectangle");
    if(indexOfWordRectangle != std::string::npos)
    {
        //Converting the XML to a command by getting the numbers
        std::string inputWithoutRectangle = userInput.substr(indexOfWordRectangle + OFFSET_RECTANGLE_WORD);

        double xCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, ' ');
        double yCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, ' ');
        double width = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, ' ');
        double height = cutFirstNumberFromStringAsDouble(inputWithoutRectangle, ' ');

        if(xCoordinate == std::numeric_limits<double>::min() || yCoordinate == std::numeric_limits<double>::min()
           || width == std::numeric_limits<double>::min() || height == std::numeric_limits<double>::min())
        {
            throw std::invalid_argument("Invalid input... coordinates (x,y, width or height) are invalid.");
        }

        const std::string color = inputWithoutRectangle;

        const auto* p = new point(xCoordinate, yCoordinate);
        Rectangle *result = new Rectangle(p, color, width, height);

        return result;
    }
    else
    {
        throw std::invalid_argument("Invalid input... the line does not contain <rect");
    }

}

Circle *CommandLineInterface::createCircleFromUserInput(const std::string &userInput)
{
    //Turns <circle cx="35.000000" cy="32.000000" r="2.000000" fill="#3399ff" />
    //into
    //create circle 32.000000 32.000000 2.000000 #3399ff
    //That is due to the fact that the SVGContainer can parse commands to create a Circle object

    int indexOfWordCircle = userInput.find("circle");
    if(indexOfWordCircle != std::string::npos)
    {
        std::string inputWithoutCircle = userInput.substr(indexOfWordCircle + OFFSET_CIRCLE_WORD);
        //Converting the XML to a command by getting the numbers

        double xCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutCircle, ' ');
        double yCoordinate = cutFirstNumberFromStringAsDouble(inputWithoutCircle, ' ');
        double radius = cutFirstNumberFromStringAsDouble(inputWithoutCircle, ' ');

        if(xCoordinate == std::numeric_limits<double>::min() || yCoordinate == std::numeric_limits<double>::min()
           || radius == std::numeric_limits<double>::min())
        {
            throw std::invalid_argument("Invalid input");
        }

        std::string color = inputWithoutCircle;

        auto* p = new point(xCoordinate, yCoordinate);
        Circle *result = new Circle(p, color, radius);

        return result;

    }
    else
    {
        throw std::invalid_argument("Invalid user input");
    }
}

Line *CommandLineInterface::createLineFromUserInput(const std::string &userInput)
{
    //Turns <line x1="24.000000" y1="25.000000" x2="22.000000" y2="22.000000" fill="#3399ff" />
    //into
    //create line 24.000000 25.000000 22.000000 22.000000 #3399ff
    //That is due to the fact that the SVGContainer can parse commands to create a Rectangle object

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
        std::string color = inputWithoutLine;

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
    //Turns <polygon points="20,20 30,30 40,40" fill="#00FFFF" />
    //into
    //create polygon 20 20 30 30 40 40 #00FFFF
    //That is due to the fact that the SVGContainer can parse commands to create a Polygon object

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
                color = inputWithoutPolygon;
                Polygon *result = new Polygon(temp, amountOfPoints / 2, color);

                return result;
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

void CommandLineInterface::fillPointsFromUserInput(point *toFill, int &amountOfPoints, std::string &inputWtihoutPolygon)
{
    //Fills an array of points from a string
    if(amountOfPoints % 2 != 0) //The count of points should be even
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

bool CommandLineInterface::exec(const std::string &userInput)
{
    if(userInput.find("create") != std::string::npos)
    {
        if(isFileOpen)
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
        else
        {
            std::cout << "No file is open...\n Please use open <file_name> to open a file\n";
        }
    }
    else if(userInput.find("save") != std::string::npos)
    {
        if(isFileOpen)
        {
            if(userInput.length() == 4)
            {
                try
                {
                    file.saveFile(shapes);
                }
                catch(std::exception& e)
                {
                    std::cout << "Unable to save file...\n" << e.what() << "\n";
                }
            }
            else if(userInput.length() > 6)
            {
                try
                {
                    file.saveAsFile(userInput, shapes);
                }
                catch(std::exception& e)
                {
                    std::cout << "Unable to save file...\n" << e.what() << "\n";
                }
            }
        }
        else
        {
            std::cout << "No file is open...\n Please use open <file_name> to open a file\n";
        }
    }
    else if(userInput.find("erase") != std::string::npos)
    {
        if(isFileOpen)
        {
            try
            {
                eraseShape(userInput);
            }
            catch(std::invalid_argument &e)
            {
                std::cout << "Cannot erase shape\n" << e.what() << "\n";
                return false;
            }
        }
        else
        {
            std::cout << "No file is open...\n Please use open <file_name> to open a file\n";
        }
    }
    else if(userInput.find("translate") != std::string::npos)
    {
        if(isFileOpen)
        {
            try
            {
                translateShape(userInput);
                return true;
            }
            catch(std::invalid_argument &e)
            {
                std::cout << "Cannot translate shape\n";
                std::cout << e.what() << "\n";
                return false;
            }
        }
        else
        {
            std::cout << "No file is open...\n Please use open <file_name> to open a file\n";
        }
    }
    else if(userInput.find("close") != std::string::npos)
    {
        if(isFileOpen)
        {
            isFileOpen = false;
            file.closeFile();
            std::cout << "File has been closed successfully";
        }
        else
        {
            std::cout << "No file is open...\n Please use open <file_name> to open a file\n";
        }
    }
    else if(userInput.find("open") != std::string::npos)
    {
        if(file.openFile(userInput) == 1)
        {
            std::cout << "File opened successfully\n";

            std::vector<std::string> commandsToCreate = file.loadIntoContainer();

            for(std::string item : commandsToCreate)
            {
                try
                {
                    createShape(item);
                }
                catch(std::invalid_argument& e)
                {
                    std::cout << "Unable to read the file\n" << e.what();
                    return false;
                }
            }
            isFileOpen = true;
        }
        else
        {
            std::cout << "File could not be opened\n";
            return false;
        }
    }
    else if(userInput.find("print") != std::string::npos)
    {
        if(isFileOpen)
        {
            try
            {
                shapes.printShapes();
            }
            catch(std::invalid_argument& e)
            {
                std::cout << "Cannot print shapes.\n" << e.what() << "\n";
            }
        }
        else
        {
            std::cout << "No file is open...\n Please use open <file_name> to open a file\n";
        }
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
            throw std::invalid_argument("Invalid command: The amount of attributes is invalid");
        }
        else
        {
            try
            {
                Rectangle *temp = createRectangleFromUserInput(userInput);
                shapes.addShape(temp);
            }
            catch(std::invalid_argument& e)
            {
                throw e;
            }
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
    //translate vertical="10" horizontal="100"
    //translate "1" vertical="20" horizontal="200"

    int indexOfWordTranslate = coordinates.find("translate");
    std::string inputWithoutTranslate = coordinates.substr(indexOfWordTranslate + OFFSET_TRANSLATE_WORD); //removes translate
    inputWithoutTranslate = removeBlankSpaces(inputWithoutTranslate);
    int idOfFigureToTranslate = -1;
    if(inputWithoutTranslate[0] != FIRST_LETTER_VERTICAL)
    {
        //Input has id
        idOfFigureToTranslate = cutFirstNumberFromStringAsInt(inputWithoutTranslate, '"');
        if(idOfFigureToTranslate == (int)std::numeric_limits<double>::min())
        {
            throw std::invalid_argument("Id of the figure is bad\n");
        }
    }

    inputWithoutTranslate = removeWordFromString("vertical=", inputWithoutTranslate);
    double vertical = cutFirstNumberFromStringAsDouble(inputWithoutTranslate, '"');
    if(vertical == std::numeric_limits<double>::min())
    {
        throw std::invalid_argument("Vertical translate is invalid\n");
    }

    inputWithoutTranslate = removeWordFromString("horizontal=", inputWithoutTranslate);
    double horizontal = cutFirstNumberFromStringAsDouble(inputWithoutTranslate, '"');
    if(horizontal == std::numeric_limits<double>::min())
    {
        throw std::invalid_argument("Horizontal translate is invalid\n");
    }

    if(idOfFigureToTranslate == -1) //If we have to translate all figures, we loop them
    {
        int s = shapes.getCount();
        for(int i = 0; i < s; i++)
        {
            try
            {
                shapes.translateShape(i, vertical, horizontal);
            }
            catch(std::invalid_argument& e)
    //coordinates = removeBlankSpaces(coordinates);
            {
                std::cout << "Horizontal or vertical args are invalid \n" << e.what();
            }
        }
    }
    else
    {
        try
        {
            shapes.translateShape(idOfFigureToTranslate-1, vertical, horizontal);
        }
        catch(std::invalid_argument& e)
        {
            std::cout << "Horizontal or vertical args are invalid \n" << e.what();
        }
    }
}

void CommandLineInterface::openFromContainer(const std::vector<std::string> &containerWithCommandsAsString)
{
    for(const std::string &input : containerWithCommandsAsString)
    {
        createShape(input);
    }
}