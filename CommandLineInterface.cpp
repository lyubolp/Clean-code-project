//
// Created by lyubo on 04.05.19.
//

#include <string>
#include <cstring>
#include "Headers/CommandLineInterface.hpp"
#include "Headers/StringManip.hpp"


CommandLineInterface &CommandLineInterface::getInstance()
{
    static CommandLineInterface instance;

    return instance;
}


std::pair<Point *, Point> CommandLineInterface::generatePointsFromUserInput(std::string &userInput, const shape &typeOf) const
{
    auto *coordinates = new Point();
    coordinates->setX(cutFirstNumberFromStringAsDouble(userInput, ' '));
    coordinates->setY(cutFirstNumberFromStringAsDouble(userInput, ' '));

    Point additionalPoints;

    additionalPoints.setX(cutFirstNumberFromStringAsDouble(userInput, ' '));

    if(typeOf == RECTANGLE || typeOf == LINE)
    {
        additionalPoints.setY(cutFirstNumberFromStringAsDouble(userInput, ' '));
    }
    else
    {
        additionalPoints.setY(0);
    }

    if(coordinates->getX() == std::numeric_limits<double>::min() ||
       coordinates->getY() == std::numeric_limits<double>::min()
       || additionalPoints.getX() == std::numeric_limits<double>::min() ||
       additionalPoints.getY() == std::numeric_limits<double>::min())
    {
        throw std::invalid_argument("Invalid input... coordinates (x,y, width or height) are invalid.");
    }

    return {coordinates, additionalPoints};
}

Rectangle *CommandLineInterface::createRectangleFromUserInput(const std::string &userInput) const
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

        try
        {
            //Point* -> X and Y; Point -> width and height
            std::pair<Point *, Point> pointsOfRectangle = generatePointsFromUserInput(inputWithoutRectangle, RECTANGLE);

            const std::string color = inputWithoutRectangle;

            Rectangle *result = new Rectangle(pointsOfRectangle.first, color, pointsOfRectangle.second.getX(),
                                              pointsOfRectangle.second.getY());
            return result;
        }
        catch(std::invalid_argument &e)
        {
            throw e;
        }
    }
    else
    {
        throw std::invalid_argument("Invalid input... the line does not contain <rect");
    }

}

Circle *CommandLineInterface::createCircleFromUserInput(const std::string &userInput) const
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

        try
        {
            //Point* -> X and Y; Point -> radius and 0
            std::pair<Point *, Point> pointsOfCircle = generatePointsFromUserInput(inputWithoutCircle, CIRCLE);

            const std::string color = inputWithoutCircle;

            Circle *result = new Circle(pointsOfCircle.first, color, pointsOfCircle.second.getX());
            return result;
        }
        catch(std::invalid_argument &e)
        {
            throw e;
        }

    }
    else
    {
        throw std::invalid_argument("Invalid user input");
    }
}

Line *CommandLineInterface::createLineFromUserInput(const std::string &userInput) const
{
    //Turns <line x1="24.000000" y1="25.000000" x2="22.000000" y2="22.000000" fill="#3399ff" />
    //into
    //create line 24.000000 25.000000 22.000000 22.000000 #3399ff
    //That is due to the fact that the SVGContainer can parse commands to create a Rectangle object

    int indexOfWordLine = userInput.find("line");
    if(indexOfWordLine != 1)
    {
        std::string inputWithoutLine = userInput.substr(indexOfWordLine + OFFSET_LINE_WORD);

        try
        {
            //Point* -> x1 and y1; Point -> x2 and y2
            std::pair<Point *, Point> pointsOfLine = generatePointsFromUserInput(inputWithoutLine, CIRCLE);

            std::string color = inputWithoutLine;

            auto *temp = new Point[2];

            temp[0] = *pointsOfLine.first;
            temp[1] = pointsOfLine.second;

            Line *result = new Line(temp, color);
            return result;
        }
        catch(std::invalid_argument &e)
        {
            throw e;
        }
    }
    return nullptr;
}


void CommandLineInterface::fillPointsFromUserInput(Point *toFill, int &amountOfPoints, std::string &inputWtihoutPolygon) const
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
        toFill[i] = Point(x, y);
    }
}

bool CommandLineInterface::execCreate(const std::string &userInput)
{
    if(isFileOpen)
    {
        try
        {
            createShape(userInput);
        }
        catch(std::invalid_argument &)
        {
            std::cout << "Error with command!";
            return false;
        }
    }
    else
    {
        std::cout << "No file is open...\n Please use open <file_name> to open a file\n";
        return false;
    }
    return true;
}

bool CommandLineInterface::execSave(const std::string &userInput) const
{
    if(isFileOpen)
    {
        try
        {
            SVGFile::getInstance().saveFile(shapes);
            return true;
        }
        catch(std::exception &e)
        {
            std::cout << "Unable to save SVGFile::getInstance()...\n" << e.what() << "\n";
            return false;
        }
    }
    else
    {
        std::cout << "No file is open...\n Please use open <file_name> to open a file\n";
        return false;
    }
}

bool CommandLineInterface::execSaveAs(const std::string &userInput) const
{
    if(isFileOpen)
    {
        try
        {
            SVGFile::getInstance().saveAsFile(userInput, shapes);
            return true;
        }
        catch(std::exception &e)
        {
            std::cout << "Unable to save SVGFile::getInstance()...\n" << e.what() << "\n";
            return false;
        }
    }
    else
    {
        std::cout << "No file is open...\n Please use open <file_name> to open a file\n";
        return false;
    }
}

bool CommandLineInterface::execErase(const std::string &userInput)
{
    if(isFileOpen)
    {
        try
        {
            eraseShape(userInput);
            return true;
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

bool CommandLineInterface::execTranslate(const std::string & userInput)
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
        return false;
    }
}

bool CommandLineInterface::execClose(const std::string &userInput)
{
    if(isFileOpen)
    {
        isFileOpen = false;
        SVGFile::getInstance().closeFile();
        std::cout << "File has been closed successfully";
        return true;
    }
    else
    {
        std::cout << "No file is open...\n Please use open <file_name> to open a file\n";
        return false;
    }
}

bool CommandLineInterface::execOpen(const std::string &userInput)
{
    if(SVGFile::getInstance().openFile(userInput) == 1)
    {
        std::cout << "File opened successfully\n";

        std::vector<std::string> commandsToCreate = SVGFile::getInstance().loadIntoContainer();

        for(const std::string& item : commandsToCreate)
        {
            try
            {
                createShape(item);
            }
            catch(std::invalid_argument &e)
            {
                std::cout << "Unable to read the file\n" << e.what();
                return false;
            }
        }
        isFileOpen = true;
        return true;
    }
    else
    {
        std::cout << "File could not be opened\n";
        return false;
    }
}

bool CommandLineInterface::execPrint(const std::string &userInput)
{
    if(isFileOpen)
    {
        try
        {
            shapes.printShapes();
            return true;
        }
        catch(std::invalid_argument &e)
        {
            std::cout << "Cannot print shapes.\n" << e.what() << "\n";
            return false;
        }
    }
    else
    {
        std::cout << "No file is open...\n Please use open <file_name> to open a file\n";
        return false;
    }
}

bool CommandLineInterface::exec(const std::string &userInput)
{
    if(userInput.find("create") != std::string::npos)
    {
        return execCreate(userInput);
    }
    else if(userInput.find("save") != std::string::npos)
    {
        if(userInput.length() == 4)
        {
            return execSave(userInput);
        }
        else
        {
            return execSaveAs(userInput);
        }
    }
    else if(userInput.find("erase") != std::string::npos)
    {
        return execErase(userInput);
    }
    else if(userInput.find("translate") != std::string::npos)
    {
        return execTranslate(userInput);
    }
    else if(userInput.find("close") != std::string::npos)
    {
        return execClose(userInput);
    }
    else if(userInput.find("open") != std::string::npos)
    {
        return execOpen(userInput);
    }
    else if(userInput.find("print") != std::string::npos)
    {
        return execPrint(userInput);
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
            catch(std::invalid_argument &e)
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

const double getValueFromCommand(std::string& userInput, const std::string& attributeToGetFrom)
{
    userInput = removeWordFromString(attributeToGetFrom, userInput);
    double result = cutFirstNumberFromStringAsDouble(userInput, '"');
    if(result == std::numeric_limits<double>::min())
    {
        throw std::invalid_argument("Vertical translate is invalid\n");
    }

    return result;
}

void CommandLineInterface::translateShape(const std::string &coordinates)
{
    //translate vertical="10" horizontal="100"
    //translate "1" vertical="20" horizontal="200"

    int indexOfWordTranslate = coordinates.find("translate");
    std::string inputWithoutTranslate = coordinates.substr(
            indexOfWordTranslate + OFFSET_TRANSLATE_WORD); //removes translate
    inputWithoutTranslate = removeBlankSpaces(inputWithoutTranslate);

    int idOfFigureToTranslate = -1;
    if(inputWithoutTranslate[0] != FIRST_LETTER_VERTICAL)
    {
        //Input has id
        idOfFigureToTranslate = cutFirstNumberFromStringAsInt(inputWithoutTranslate, '"');
        if(idOfFigureToTranslate == (int) std::numeric_limits<double>::min())
        {
            throw std::invalid_argument("Id of the figure is bad\n");
        }
    }

    double vertical = getValueFromCommand(inputWithoutTranslate, "vertical=");
    double horizontal = getValueFromCommand(inputWithoutTranslate, "horizontal=");

    if(idOfFigureToTranslate == -1) //If we have to translate all figures, we loop them
    {
        int s = shapes.getCount();
        for(int i = 0; i < s; i++)
        {
            try
            {
                shapes.translateShape(i, vertical, horizontal);
            }
            catch(std::invalid_argument &e)
            {
                std::cout << "Horizontal or vertical args are invalid \n" << e.what();
            }
        }
    }
    else
    {
        try
        {
            shapes.translateShape(idOfFigureToTranslate - 1, vertical, horizontal);
        }
        catch(std::invalid_argument &e)
        {
            std::cout << "Horizontal or vertical args are invalid \n" << e.what();
        }
    }
}
